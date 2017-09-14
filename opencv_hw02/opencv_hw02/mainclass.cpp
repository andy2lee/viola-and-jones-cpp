/*
Author: kanazawa
Date: 8/28/2017
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include "database.h"
#include "feature_detecting.h"
#include "integral_image.h"
#include "weight_calculating.h"
#include "save_temp_sorted.h"
#include "threshold.h"
#include "error_rate.h"
#include "classifier_saving.h"
#include "detect_correct_wrong_table.h"
#include "results.h" ///cargos for testing
#include "strong_classifier.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
	int picture_nums = 110;
	int human_face = 10, non_human_face = 100;
	int feature_numbers = 0;
	int Tt_training = 40;
	integral_image *inter_ig;
	feature_detecting *ft_dt;
	std::string to_s;
	database<int> *data = new database<int>[picture_nums]();
	Mat image;
	int det_true_false;
	for (int i = 0; i < picture_nums; i++) {
		if (i < 10){
			to_s = to_string(i + 1);
			image = imread("faces_data/1 (" + to_s + ").bmp", CV_LOAD_IMAGE_GRAYSCALE);
			det_true_false = 1;
		}
		else {
			to_s = to_string(i - 10 + 1);
			image = imread("faces_data/noface (" + to_s + ").bmp", CV_LOAD_IMAGE_GRAYSCALE);
			det_true_false = 0;
		}
		(data + i)->initualize_array_image_array_integral(image.rows, image.cols, det_true_false);
		(data + i)->store_pixel(image);
		//calculate the integral image and save them into the array_integral;
		for (int j_s = 0; j_s < image.rows; j_s++) {
			for (int i_s = 0; i_s < image.cols; i_s++) {
				inter_ig = new integral_image(i_s, j_s, data + i);
				inter_ig->integral_working();
				delete inter_ig;
			}
		}
		ft_dt = new feature_detecting((data + i)->output_array_integral(), (data + i)->output_array_image(), (data + i)->output_array_feature(), image.rows, image.cols);
		ft_dt->save_to_database();
		feature_numbers = ft_dt->output_feature_numbers();
		delete ft_dt;
		//int a = data->total_of_feature();
		//cout << "numbers:" << i << endl;
		//(data + i)->checking_array_integral(); //checking point
	}

	//--====>需要訓練五次
	//1.正規化權重，使得Wt具有機率分佈
	weight_calculating *wt_cal = new weight_calculating(picture_nums, human_face, non_human_face, data);
	classifier_saving<double> *clfer_saving = new classifier_saving<double>(feature_numbers, Tt_training);//需放在for(5)的訓練外宣告
	for (int i = 0; i < picture_nums; i++)
		(data + i)->input_weight(wt_cal->weight_initualize(i));
	results<double> *result = new results<double>(Tt_training);///cargos for testing


	for (int Tt_training_loop = 0; Tt_training_loop < Tt_training; Tt_training_loop++) {
		wt_cal->balance_weight_initualize();
		//2.對於每個特徵j，訓練成一個分類器hj只僅限使用於單一功能
		save_temp_sorted<int> *s_temp = new save_temp_sorted<int>(picture_nums);
		error_rate<double> *error_r = new error_rate<double>(feature_numbers);

		detect_correct_wrong_table<int> *detect_y_n = new detect_correct_wrong_table<int>(feature_numbers, picture_nums);
		cout << "waiting for process..." << endl;
		for (int select_feature_j = 0; select_feature_j < feature_numbers; select_feature_j++) { //feature_numbers變數 43200 (instead of)
			for (int n = 0; n < picture_nums; n++) {
				s_temp->input_temp_feature((data + n)->select_output_pivot(select_feature_j), n);
			}
			s_temp->sorting_feature_numbers();
			//s_temp->print_all_numbers();//testing
			threshold *ths = new threshold(s_temp, data, feature_numbers, picture_nums, select_feature_j);
			ths->detecting_threshold_process();
			ths->weak_classifier_obj_process(error_r, clfer_saving, detect_y_n);
			delete ths;
		}
		error_r->print_all(result, Tt_training_loop);
		//3.取出具有低錯誤率的分類器成為ht==>即為最佳弱分類器
		clfer_saving->input_the_best_classifier(error_r->output_t_p_the_best_classifier(), Tt_training_loop);
		
		cout << "====================" << endl;
		cout << *(clfer_saving->best_clfer_feature_pivot + Tt_training_loop) << endl;
		cout << *(clfer_saving->best_clfer_p_value_arr + Tt_training_loop) << endl;
		cout << *(clfer_saving->best_clfer_threshold_arr + Tt_training_loop) << endl;
		cout << "====================" << endl;
		cout << error_r->output_t_p_the_best_classifier() << endl;
		cout << clfer_saving->output_the_best_p_value(error_r->output_t_p_the_best_classifier()) << endl;
		cout << clfer_saving->output_the_best_threshold(error_r->output_t_p_the_best_classifier()) << endl;
		cout << "--------------" << endl;
		detect_y_n->output_detect_yes_no_table(error_r->output_t_p_the_best_classifier(), result, Tt_training_loop);///cargos for testing ===>result 和 Tt_training_loop 原本是沒有放入變數的
		cout << "--------------" << endl;
		result->t_point_t[Tt_training_loop] = *(clfer_saving->best_clfer_feature_pivot + Tt_training_loop);///cargos for testing
		result->p_value_t[Tt_training_loop] = *(clfer_saving->best_clfer_p_value_arr + Tt_training_loop);///cargos for testing
		result->threshold_t[Tt_training_loop] = *(clfer_saving->best_clfer_threshold_arr + Tt_training_loop);///cargos for testing

		//detect_y_n->output_all_table();
		
		//data;;detect_y_n

		//clfer_saving->print_of_classifier();
		//4.更新所有權重
		wt_cal->weight_calculating_process(detect_y_n, error_r->output_t_p_the_best_classifier(), error_r->output_min_error());
		delete s_temp;
		delete error_r;
		delete detect_y_n;
	}
	result->output_all_result();///cargos for testing

	delete clfer_saving;
	delete wt_cal;
	cout << "====================" << endl;
	cout << "end" << endl;

	//version01 edit: add The final strong classifier for the function by using the cargos
	cout << "now testing" << endl;


	database<int> *data_testing = new database<int>[picture_nums]();
	feature_detecting *ft_dt_testing;
	Mat image_testing;
	for (int i = 0; i < picture_nums; i++)
	{
		strong_classifier *st_clfer = new strong_classifier(result);
		if (i < 10) {
			to_s = to_string(i + 1);
			image_testing = imread("faces_data/1 (" + to_s + ").bmp", CV_LOAD_IMAGE_GRAYSCALE);
			det_true_false = 1;
		}
		else {
			to_s = to_string(i - 10 + 1);
			image_testing = imread("faces_data/noface (" + to_s + ").bmp", CV_LOAD_IMAGE_GRAYSCALE);
			det_true_false = 0;
		}
		(data_testing + i)->initualize_array_image_array_integral(image_testing.rows, image_testing.cols, det_true_false);
		(data_testing + i)->store_pixel(image_testing);

		for (int j_s = 0; j_s < image_testing.rows; j_s++) {
			for (int i_s = 0; i_s < image_testing.cols; i_s++) {
				inter_ig = new integral_image(i_s, j_s, data_testing + i);
				inter_ig->integral_working();
				delete inter_ig;
			}
		}
		ft_dt_testing = new feature_detecting((data_testing + i)->output_array_integral(), (data_testing + i)->output_array_image(), (data_testing + i)->output_array_feature(), image_testing.rows, image_testing.cols);
		ft_dt_testing->save_to_database();
		feature_numbers = ft_dt_testing->output_feature_numbers();
		delete ft_dt_testing;

		for (int i_i = 0; i_i < Tt_training; i_i++) {
			st_clfer->strong_classifier_processing(result->output_p(i_i), data_testing, i_i, i);
		}
		int ans = st_clfer->judgment_face();
		delete st_clfer;
		cout << ans;
	}
	//strong classifier algorithm
	cout << endl;
	waitKey(0);
	system("pause");
	return 0;
}