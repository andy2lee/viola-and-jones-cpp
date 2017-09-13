#pragma once
#include "results.h"
#include "database.h"
#include <math.h>
#include <iostream>

class strong_classifier
{
private:
	results<double> *result;
	double *Et;
	double left_total = 0.0;
	double right_total = 0.0;

public:
	strong_classifier(results<double> *);
	~strong_classifier();
	void strong_classifier_processing(int, database<int> *, int);
	int judgment_face();
};

