#include "weak_classifier.h"



weak_classifier::weak_classifier(save_temp_sorted<int> *s_temp, database<int> *data, error_rate<double> *error_r, double all_of_min, int p_value, int feature_numbers, int picture_nums, int select_feature_j, classifier_saving<double> *clfer_saving, detect_correct_wrong_table<int> *detect_y_n)
{
	this->s_temp = s_temp;
	this->data = data;
	this->all_of_min = all_of_min;
	this->p_value = p_value;
	this->feature_numbers = feature_numbers;
	this->picture_nums = picture_nums;
	this->error_r = error_r;
	this->select_feature_j = select_feature_j;
	this->clfer_saving = clfer_saving;
	this->detect_y_n = detect_y_n;
}


weak_classifier::~weak_classifier()
{
	//delete s_temp;
	//delete data;
	//delete error_r;
	//delete clfer_saving;
	//delete detect_y_n;
}

void weak_classifier::weak_classifier_processing() {
	int output_result;
	double total_error = 0.0;
	save_h_to_classifer_saving(p_value, all_of_min, select_feature_j);
;	for (int i = 0; i < picture_nums; i++) {
		if (p_value * (data + i)->select_output_pivot(select_feature_j) < p_value * all_of_min) {
			output_result = 1;
		}
		else {
			output_result = 0;
		}
		if (output_result == (data + i)->output_boolean()) {
			detect_y_n->input_detect_yes_no_table(select_feature_j, i, 1);
		}
		else {
			detect_y_n->input_detect_yes_no_table(select_feature_j, i, 0);
		}
		total_error += (data + i)->output_weight() * abs(output_result - (data + i)->output_boolean());
	}
	error_r->input_error_rate_array(total_error, select_feature_j);
}

void weak_classifier::save_h_to_classifer_saving(int p_value, double all_of_min, int select_feature_j) {
	clfer_saving->input_each_classifier(p_value, all_of_min, select_feature_j);
}