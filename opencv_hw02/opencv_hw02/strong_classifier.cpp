#include "strong_classifier.h"



strong_classifier::strong_classifier(results<double> *result)
{
	this->result = result;
	this->Et = result->Et;
	this->p_value_t = result->p_value_t;
	this->threshold_t = result->threshold_t;
}


strong_classifier::~strong_classifier()
{
}

void strong_classifier::strong_classifier_processing(int pivot_t_p, database<int> *data_testing, int i) {
	cout << Et[i] << ";;" << pivot_t_p << endl;
	double Bt = Et[i] / (1.0 - Et[i]);
	double alpha = log10(1.0 / Bt);

	left_total = left_total + (alpha * ht_func(pivot_t_p, i, data_testing));
	right_total = right_total + ((1.0 / 2.0) * alpha);
	cout << left_total << " ; " << right_total << " ; " << (data_testing + 0)->select_output_pivot(pivot_t_p) << " ; " << pivot_t_p << " ; " << alpha << " ; " << Bt << " ; " << Et[i] << endl;
}

int strong_classifier::judgment_face() {
	if (left_total >= right_total) {
		return 1;
	}
	else {
		return 0;
	}
}

double strong_classifier::ht_func(int pivot_t_p, int i, database<int> *data_testing) {
	if (p_value_t[i] * (data_testing + 0)->select_output_pivot(pivot_t_p) < p_value_t[i] * threshold_t[i]) {
		return 1.0;
	}
	else {
		return 0.0;
	}
}