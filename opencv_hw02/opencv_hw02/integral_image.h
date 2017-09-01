#pragma once
#include "database.h"

class integral_image
{
public:
	integral_image(int, int, database<int>*);
	~integral_image();
	void integral_working();
private:
	int temp = 0;
	int i_point = 0, j_point = 0;
	int **array_image, **array_integral;
	int temp_calculate_s_straight();
	int pivot_point_value();
};

