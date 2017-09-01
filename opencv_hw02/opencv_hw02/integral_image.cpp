#include "integral_image.h"


integral_image::integral_image(int i_input_point, int j_input_point, database<int>* input_database)
{
	this->i_point = i_input_point;
	this->j_point = j_input_point;
	this->array_image = input_database->output_array_image();
	this->array_integral = input_database->output_array_integral();
}


integral_image::~integral_image()
{
	
}

int integral_image::temp_calculate_s_straight() 
{
	int temp_total_straight = 0;
	if (j_point - 1 < 0) {
		temp_total_straight = 0;
	}
	else
	{
		for (int count_move = 0; count_move < j_point; count_move++)
		{
			temp_total_straight += array_image[count_move][i_point];
		}
	}
	return temp_total_straight;
}
int integral_image::pivot_point_value() 
{
	return array_image[j_point][i_point];
}

void integral_image::integral_working()
{
	int array_integral_result = 0;
	if (i_point - 1 < 0) {
		array_integral_result = 0;
	}
	else
	{
		array_integral_result = array_integral[j_point][i_point - 1];
	}
	array_integral[j_point][i_point] = array_integral_result + temp_calculate_s_straight() + pivot_point_value();
}