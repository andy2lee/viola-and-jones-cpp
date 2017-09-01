#pragma once
#include <iostream>
using namespace std;

template <class T>
class classifier_saving
{
private:
	int *p_value_save;
	double *all_of_threshold_min;
	int feature_numbers = 0;
	// the best classifier

public:
	int Tt_training = 0;
	int *best_clfer_p_value_arr;
	int *best_clfer_feature_pivot;
	double *best_clfer_threshold_arr;
	classifier_saving(int feature_numbers, int Tt_training) {
		p_value_save = new int[feature_numbers];
		all_of_threshold_min = new double[feature_numbers];
		this->feature_numbers = feature_numbers;

		best_clfer_p_value_arr = new int[Tt_training];
		best_clfer_threshold_arr = new double[Tt_training];
		best_clfer_feature_pivot = new int[Tt_training];
	}
	~classifier_saving() {

	}


	void input_each_classifier(int p_value, double all_of_min, int select_feature_j) {
		p_value_save[select_feature_j] = p_value;
		all_of_threshold_min[select_feature_j] = all_of_min;
	}

	void print_of_classifier() {
		for (int n = 0; n < feature_numbers; n++) {
			cout << all_of_threshold_min[n] << " , " << p_value_save[n] << endl;
		}
	}

	int output_the_best_p_value(int pivot) {
		return p_value_save[pivot];
	}

	T output_the_best_threshold(int pivot) {
		return all_of_threshold_min[pivot];
	}

	void input_the_best_classifier(int t_p, int Tt_training) {
		best_clfer_feature_pivot[Tt_training] = t_p;
		best_clfer_p_value_arr[Tt_training] = p_value_save[t_p];
		best_clfer_threshold_arr[Tt_training] = all_of_threshold_min[t_p];
	}
};
