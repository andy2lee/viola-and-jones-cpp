#include "threshold.h"


threshold::threshold(save_temp_sorted<int> *s_temp_ths, database<int> *data_ths, int feature_numbers, int picture_nums, int select_feature_j)
{
	this->s_temp_ths = s_temp_ths;
	this->data_ths = data_ths;
	this->feature_numbers = feature_numbers;
	this->picture_nums = picture_nums;
	this->select_feature_j = select_feature_j;
}


threshold::~threshold()
{

}

void threshold::detecting_threshold_process() {
	int picture_nums = s_temp_ths->output_picture_nums();
	double T_plus = 0.0, T_minus = 0.0;
	double first = -1.0, last = 300.0;
	double average = 0.0, average_double = 0.0;//average 是拿來當判斷依據，無數據可言
	for (int i = 0; i < picture_nums; i++) {
		if ((data_ths + i)->output_boolean() == 1)
			T_plus += (data_ths + i)->output_weight();
		if ((data_ths + i)->output_boolean() == 0)
			T_minus += (data_ths + i)->output_weight();
	}
	//cout << T_plus << ";" << T_minus << "testing T_plus T_minus" << endl;//testing
	//cout << "====================" << endl;

	double *left_e_array = new double[picture_nums + 1];
	double *right_e_array = new double[picture_nums + 1];

	for (int i = 0; i < picture_nums; i++) {
		//cout << s_temp_ths->select_sorted_feature_numbers_array(i) << endl;//testing
		if (i == 0) {
			average_double = ((first + s_temp_ths->select_sorted_feature_value_array(i)) / 2.0);
			average = ((s_temp_ths->select_sorted_feature_value_array(i) + s_temp_ths->select_sorted_feature_value_array(i + 1)) / 2.0);
		}
		else if (i == picture_nums - 1)
			average = ((s_temp_ths->select_sorted_feature_value_array(i) + last) / 2.0);
		else
			average = ((s_temp_ths->select_sorted_feature_value_array(i) + s_temp_ths->select_sorted_feature_value_array(i + 1)) / 2.0);

		//cout << average << endl;

		if (i == 0) {
			double S_plus = 0.0, S_minus = 0.0;
			double S_plus_first = 0.0, S_minus_first = 0.0;
			for (int n = 0; n < picture_nums; n++) {
				if ((data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_boolean() == 1) {
					if (s_temp_ths->select_sorted_feature_value_array(n) < average_double) {
						S_plus_first += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
					}
					if (s_temp_ths->select_sorted_feature_value_array(n) < average) {
						S_plus += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
					}
				}
				else if (((data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_boolean() == 0)) {
					if (s_temp_ths->select_sorted_feature_value_array(n) < average_double) {
						S_minus_first += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
					}
					if (s_temp_ths->select_sorted_feature_value_array(n) < average) {
						S_minus += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
					}
				}
			}
			left_e_array[picture_nums + 1 - 1] = (S_plus_first + (T_minus - S_minus_first));
			right_e_array[picture_nums + 1 - 1] = (S_minus_first + (T_plus - S_plus_first));
			left_e_array[i] = (S_plus + (T_minus - S_minus));
			right_e_array[i] = (S_minus + (T_plus - S_plus));
			//cout << (S_plus_first + (T_minus - S_minus_first)) << " , " << (S_minus_first + (T_plus - S_plus_first)) << endl;
			//cout << (S_plus + (T_minus - S_minus)) << " , " << (S_minus + (T_plus - S_plus)) << endl;

			//cout << S_plus_first << ", " << S_minus_first << endl;
			//cout << S_plus << ", " << S_minus << endl;
		}
		else {
			double S_plus = 0.0, S_minus = 0.0;
			for (int n = 0; n < picture_nums; n++) {
				if (s_temp_ths->select_sorted_feature_value_array(n) < average && (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_boolean() == 1) {
					S_plus += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
				}
				else if (s_temp_ths->select_sorted_feature_value_array(n) < average && (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_boolean() == 0) {
					S_minus += (data_ths + s_temp_ths->select_sorted_feature_numbers_array(n))->output_weight();
				}
			}
			left_e_array[i] = (S_plus + (T_minus - S_minus));
			right_e_array[i] = (S_minus + (T_plus - S_plus));
			//cout << (S_plus + (T_minus - S_minus)) << " , " << (S_minus + (T_plus - S_plus)) << endl;

			//cout << S_plus << ", " << S_minus << endl;
		}
	}

	//double *left_e_array = new double[picture_nums + 1];
	//double *right_e_array = new double[picture_nums + 1];

	double left_min = 0.0, right_min = 0.0;
	double all_of_min = 0.0;
	left_min = left_e_array[0];
	right_min = right_e_array[0];
	for (int n = 0; n < picture_nums + 1; n++) {
		if (left_e_array[n] < left_min)
			left_min = left_e_array[n];
		if (right_e_array[n] < right_min)
			right_min = right_e_array[n];
	}
	if (left_min < right_min) {
		all_of_min = left_min;
		p_value = -1;
	}
	else {
		all_of_min = right_min;
		p_value = 1;
	}
	this->all_of_min = all_of_min;
	//cout << left_min << " " << right_min << endl;
	
	//for (int t = 0; t < 111; t++)
	//	cout << left_e_array[t] << " , " << right_e_array[t] << endl;
	delete left_e_array;
	delete right_e_array;
}

void threshold::weak_classifier_obj_process(error_rate<double> *error_r, classifier_saving<double> *clfer_saving, detect_correct_wrong_table<int> *detect_y_n) {
	weak_classifier *wk_class = new weak_classifier(s_temp_ths, data_ths, error_r, all_of_min, p_value, feature_numbers, picture_nums, select_feature_j, clfer_saving, detect_y_n);
	wk_class->weak_classifier_processing();
	delete wk_class;
}