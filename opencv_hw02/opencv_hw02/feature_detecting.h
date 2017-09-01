#pragma once
#include <math.h>
#include <iostream>
using namespace std;

class feature_detecting
{
private:
	int **array_image;
	int **array_integral;
	int *array_feature;
	int rows_size, cols_size;
	int feature_numbers;
public:
	feature_detecting(int **, int **, int *, int, int);
	~feature_detecting();
	void save_to_database();
	int output_feature_numbers();
};

