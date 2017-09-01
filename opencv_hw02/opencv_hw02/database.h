#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

template <class T> 
class database
{
private:
	T **array_image;
	T **array_integral;
	T *array_feature = new T[43200];
	T rows_size, cols_size;
	double weight;
	int boolean_true_false;
public:
	database() {

	}

	~database() {

	}

	void initualize_array_image_array_integral(T rows_size, T cols_size, int input_boolean_real_fake){
		array_image = new T *[rows_size];
		array_integral = new T *[rows_size];
		for (int i = 0; i < rows_size; i++) {
			*(array_image + i) = new T[cols_size];
			*(array_integral + i) = new T[cols_size];
		}
		this->rows_size = rows_size;
		this->cols_size = cols_size;
		this->boolean_true_false = input_boolean_real_fake;
	}

	void store_pixel(Mat image_input) {
		for (int j = 0; j < image_input.rows; j++) {
			for (int i = 0; i < image_input.cols; i++) {
				*(*(array_image + j) + i) = image_input.at<uchar>(j, i);
			}
		}
	}

	void checking_array_integral() {
		int total = 0;
		for (int num_r = 0; num_r < rows_size; num_r++) {
			for (int num_c = 0; num_c < cols_size; num_c++) {
				total += array_image[num_r][num_c];
			}
		}
		if (total != array_integral[rows_size - 1][cols_size - 1])
			cout << "wrong" << endl;
		else
			cout << "right" << endl;
		cout << "array_integral_23, 23 position=>" << array_integral[rows_size - 1][cols_size - 1] << endl;
	}

	T **output_array_image() {
		return array_image;
	}

	T **output_array_integral() {
		return array_integral;
	}
	
	T *output_array_feature() {
		return array_feature;
	}
	
	T select_output_pivot(int pivot) {
		return array_feature[pivot];
	}

	int output_boolean() {
		return boolean_true_false;
	}

	void input_weight(double input_new_weight) {
		this->weight = input_new_weight;
	}

	double output_weight() {
		return weight;
	}

	void print_all_feature() {
		for (int i = 0; i < 43200; i++) {
			cout << array_feature[i] << endl;
		}
	}
};