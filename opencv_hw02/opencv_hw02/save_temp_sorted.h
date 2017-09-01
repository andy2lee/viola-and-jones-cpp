#pragma once
#include <iostream>
using namespace std;

template <class T>
class save_temp_sorted
{
private:
	T picture_nums;
	T *sorted_feature_value_array;
	T *sorted_feature_numbers_array;
public:
	save_temp_sorted(T picture_nums) {
		this->picture_nums = picture_nums;
		this->sorted_feature_numbers_array = new T[picture_nums];
		this->sorted_feature_value_array = new T[picture_nums];
	}
	~save_temp_sorted() {
		//delete sorted_feature_numbers_array;
		//delete sorted_feature_value_array;
	}

	void input_temp_feature(int input_feature_j, int pivot) {
		sorted_feature_numbers_array[pivot] = pivot;
		sorted_feature_value_array[pivot] = input_feature_j;
	}

	void sorting_feature_numbers() {
		int compare = 0, compare_number = 0;
		for (int n = 1; n < picture_nums; n++) {
			compare = sorted_feature_value_array[n];
			compare_number = sorted_feature_numbers_array[n];
			for (int t = n; t >= 0; t--) {
				if (compare < sorted_feature_value_array[t - 1]) {
					sorted_feature_value_array[t] = sorted_feature_value_array[t - 1];
					sorted_feature_value_array[t - 1] = compare;
					sorted_feature_numbers_array[t] = sorted_feature_numbers_array[t - 1];
					sorted_feature_numbers_array[t - 1] = compare_number;
				}
			}
		}
	}

	void print_all_numbers() {//testing
		for (int n = 0; n < picture_nums; n++) {//picture_nums = 110
			cout << sorted_feature_numbers_array[n] << endl;
			cout << sorted_feature_value_array[n] << endl;
			cout << "==============================" << endl;
		}
	}

	T output_picture_nums() {
		return picture_nums;
	}

	T *output_sorted_feature_value_array() {
		return sorted_feature_value_array;
	}

	T *output_sorted_feature_numbers_array() {
		return sorted_feature_numbers_array;
	}



	T select_sorted_feature_value_array(int selecting) {
		return sorted_feature_value_array[selecting];
	}

	T select_sorted_feature_numbers_array(int selecting) {
		return sorted_feature_numbers_array[selecting];
	}

};