#pragma once
#include "database.h"
#include "save_temp_sorted.h"
#include <math.h>
#include "error_rate.h"
#include "classifier_saving.h"
#include "detect_correct_wrong_table.h"

class weak_classifier
{
private:
	save_temp_sorted<int> *s_temp;
	database<int> *data;
	error_rate<double> *error_r;
	classifier_saving<double> *clfer_saving;
	detect_correct_wrong_table<int> *detect_y_n;
	double all_of_min = 0.0;
	int p_value = 0;
	int feature_numbers = 0;
	int picture_nums = 0;
	int select_feature_j = 0;
public:
	weak_classifier(save_temp_sorted<int> *, database<int> *, error_rate<double> *, double, int, int, int, int, classifier_saving<double> *, detect_correct_wrong_table<int> *);
	~weak_classifier();
	void weak_classifier_processing();
	void save_h_to_classifer_saving(int, double, int);
};

