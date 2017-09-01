#pragma once
#include <iostream>
#include "results.h"///cargos for testing
using namespace std;

template <class T>
class detect_correct_wrong_table
{
public:
	detect_correct_wrong_table(int feature_numbers, int picture_nums) {
		array_table = new T*[feature_numbers];
		for (int i = 0; i < feature_numbers; i++) {
			*(array_table + i) = new T[picture_nums];
		}
		this->picture_nums = picture_nums;
		this->feature_numbers = feature_numbers;
	}
	~detect_correct_wrong_table() {
		for (int i = 0; i < feature_numbers; i++) {
			delete[] array_table[i];
		}
		delete[] array_table;
	}

	void input_detect_yes_no_table(T select_feature_j, T picture_nums_i, T boolean_y_n) {
		array_table[select_feature_j][picture_nums_i] = boolean_y_n;
	}

	void output_detect_yes_no_table(int select_feature_j, results<double> * result, int Tt_training_loop) {///cargos for testing ===>result 和 Tt_training_loop原本是沒有放入變數的
		int correct = 0;
		for (int i = 0; i < picture_nums; i++) {
			cout << array_table[select_feature_j][i];
			if (array_table[select_feature_j][i] == 1)
				correct++;
		}
		cout << "\tcorrect num : " << correct << endl;
		result->correct[Tt_training_loop] = correct;///cargos for testing
	}

	void output_all_table() {
		for (int j = 0; j < feature_numbers; j++) {
			int correct = 0;
			for (int i = 0; i < picture_nums; i++) {
				cout << array_table[j][i] ;
				if (array_table[j][i] == 1)
					correct++;
			}
			cout << "\tcorrect num : " << correct << endl;
		}
	}

	int output_select_detect_yes_no_table(int pivot, int i) {
		return array_table[pivot][i];
	}

private:
	T **array_table;
	int picture_nums;
	int feature_numbers;
};