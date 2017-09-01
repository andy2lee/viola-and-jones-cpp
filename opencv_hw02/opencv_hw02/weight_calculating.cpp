#include "weight_calculating.h"


weight_calculating::weight_calculating(int picture_nums, int human_face, int non_human_face, database<int> *data)
{
	this->picture_nums = picture_nums;
	this->human_face = human_face;
	this->non_human_face = non_human_face;
	this->data = data;
}


weight_calculating::~weight_calculating()
{

}

double weight_calculating::weight_initualize(int pivot_nums) {
	double ans = 0.0;

	if (pivot_nums < human_face)
		ans = (1.0 / (2.0 * human_face));
	else
		ans = (1.0 / (2.0 * non_human_face));
	return ans;
}

void weight_calculating::weight_calculating_process(detect_correct_wrong_table<int> *detect_y_n, int pivot, double min_error) {
	double ei = 0.0;
	double Bt = 0.0;
	Bt = min_error / (1.0 - min_error);
	for (int i = 0; i < picture_nums; i++) {
		if (detect_y_n->output_select_detect_yes_no_table(pivot, i) == 1)
			ei = 0.0;
		else
			ei = 1.0;
		(data + i)->input_weight((data + i)->output_weight() * pow(Bt, 1.0 - ei));
	}
}

void weight_calculating::balance_weight_initualize() {
	double total = 0.0;
	for (int n = 0; n < picture_nums; n++) {
		total += (data + n)->output_weight();
	}
	for (int n = 0; n < picture_nums; n++) {
		(data + n)->input_weight((data + n)->output_weight() / total);
	}
}
