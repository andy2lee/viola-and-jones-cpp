#pragma once
#include "save_temp_sorted.h"
#include "database.h"
#include "weak_classifier.h"
#include "error_rate.h"
#include "classifier_saving.h"
#include "detect_correct_wrong_table.h"

class threshold
{
private:
	save_temp_sorted<int> *s_temp_ths;
	database<int> *data_ths;
	int p_value = 0;
	double all_of_min = 0.0;
	int feature_numbers = 0;
	int picture_nums = 0;
	int select_feature_j = 0;
public:
	threshold(save_temp_sorted<int> * , database<int> *, int, int, int);
	~threshold();
	void detecting_threshold_process();
	void weak_classifier_obj_process(error_rate<double> *, classifier_saving<double> *, detect_correct_wrong_table<int> *);
};

