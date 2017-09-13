#include "strong_classifier.h"



strong_classifier::strong_classifier(results<double> *result)
{
	this->result = result;
	this->Et = result->Et;
}


strong_classifier::~strong_classifier()
{
}

void strong_classifier::strong_classifier_processing(int pivot_t_p, database<int> *data_testing, int i) {
	cout << Et[i] << ";;" << pivot_t_p << endl;
	double Bt = Et[i] / (1.0 - Et[i]);
	double alpha = log10(1.0 / Bt);
	left_total = left_total + (alpha * (data_testing + 0)->select_output_pivot(pivot_t_p));
	right_total = right_total + ((1.0 / 2.0) * alpha);
}

int strong_classifier::judgment_face() {
	cout << left_total << ";" << right_total << endl;
	if (left_total >= right_total) {
		return 1;
	}
	else {
		return 0;
	}
}