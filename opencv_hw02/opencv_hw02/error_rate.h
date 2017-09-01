#pragma once
#include <iostream>
#include "results.h"///cargos for testing
using namespace std;

template <class T>
class error_rate
{
private:
	int feature_numbers = 0;
	T *error_rate_array;
	int t_p = 0;
	T min_error = 0.0;
public:
	error_rate(int feature_numbers) {
		this->feature_numbers = feature_numbers;
		error_rate_array = new double[feature_numbers];//43200 array list
	}
	~error_rate() {
		delete error_rate_array;
		//delete error_rate_array;
	}
	void input_error_rate_array(T error_rate, int select_feature_j) {
		error_rate_array[select_feature_j] = error_rate;
	}

	void print_all(results<double> * result, int Tt_training_loop) {///cargos for testing ===>result 和 Tt_training_loop原本是沒有放入變數的
		for (int n = 0; n < feature_numbers; n++)
			cout << error_rate_array[n] << " ";
		cout << endl;
		T min = error_rate_array[0];
		//int t_p = 0;
		for (int t = 0; t < feature_numbers; t++) {
			if (error_rate_array[t] < min) {
				min = error_rate_array[t];
				t_p = t;
			}
		}
		min_error = min;
		cout << "min value : " << min << endl;
		result->Et[Tt_training_loop] = min;///cargos for testing
		cout << "t pivot : " << t_p << endl;
		/*
		bool flag = false;
		for (int t = 0; t < feature_numbers; t++) {
			if (error_rate_array[t] == min) {
				flag = true;
			}
		}
		if (flag == true) {
			cout << "duplicated min numbers" << endl;
		}
		*/
	}

	int output_t_p_the_best_classifier() {
		return t_p;
	}

	T output_min_error() {
		return min_error;
	}
};