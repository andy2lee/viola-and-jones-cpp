#include "feature_detecting.h"



feature_detecting::feature_detecting(int **input_array_integral, int **input_array_image, int *input_array_feature, int input_rows_size, int input_cols_size)
{
	this->array_integral = input_array_integral;
	this->array_feature = input_array_feature;
	this->rows_size = input_rows_size;
	this->cols_size = input_cols_size;
}


feature_detecting::~feature_detecting()
{
	//delete array_image;
	//delete array_integral;
	//delete array_feature;
}

void feature_detecting::save_to_database() {
	//==============vertical
	int p01_y = 0, p01_x = 0;
	int p02_y = 0, p02_x = 0;
	int p03_y = 1, p03_x = 0;
	int p04_y = 1, p04_x = 0;
	int counting = 0;
	int stop_move_x = 0, stop_move_y = 0;

	int except_bl_B = 0, except_bl_D = 0;
	int except_wh_B = 0, except_wh_C = 0, except_wh_D = 0;
	int black = 0, white = 0, ans = 0;

	for (int extend_y = 0; extend_y < rows_size / 2; extend_y++) {
		p02_y = extend_y;
		p03_y = extend_y + 1;
		p04_y = extend_y * 2 + 1;
		for (int extend_x = 0; extend_x < cols_size; extend_x++) {
			p02_x = extend_x;
			p04_x = extend_x;
			stop_move_y = p04_y;
			for (int movey = 0; stop_move_y < rows_size; movey++) {
				stop_move_x = p04_x;
				for (int movex = 0; stop_move_x < cols_size; movex++) {
					//cout << "(" << p01_y << ", " << p01_x << ")" << "(" << p02_y << ", " << p02_x << ")" << "(" << p03_y << ", " << p03_x << ")" << "(" << p04_y << ", " << p04_x << ")" << endl;
					//
					if (p01_y - 1 < 0 || p01_x - 1 < 0)
						except_wh_D = 0;
					else
						except_wh_D = array_integral[p01_y - 1][p01_x - 1];
					if (p01_y - 1 < 0 || p04_x < 0)
						except_wh_C = 0;
					else except_wh_C = array_integral[p01_y - 1][p04_x];
					if (p02_y < 0 || p01_x - 1 < 0) {
						except_wh_B = 0;
						except_bl_D = 0;
					}
					else {
						except_wh_B = array_integral[p02_y][p01_x - 1];
						except_bl_D = except_wh_B;
					}
					if (p04_y < 0 || p03_x - 1 < 0)
						except_bl_B = 0;
					else except_bl_B = array_integral[p04_y][p03_x - 1];

					black = array_integral[p04_y][p04_x] - except_bl_B - array_integral[p02_y][p02_x] + except_bl_D;
					white = array_integral[p02_y][p02_x] - except_wh_B - except_wh_C + except_wh_D;
					
					array_feature[counting] = abs(black - white);
					//cout << array_feature[counting] << endl;
					
					p01_x++;
					p02_x++;
					p03_x++;
					p04_x++;
					counting++;
					stop_move_x++;
				}
				p01_y++;
				p02_y++;
				p03_y++;
				p04_y++;

				p01_x = 0;
				p02_x = extend_x;
				p03_x = 0;
				p04_x = extend_x;
				stop_move_y++;
			}
			p01_y = 0;
			p02_y = extend_y;
			p03_y = extend_y + 1;
			p04_y = extend_y * 2 + 1;
		}
	}
	//==============horizontal
	p01_y = 0, p01_x = 0;
	p02_y = 0, p02_x = 0;
	p03_y = 0, p03_x = 1;
	p04_y = 0, p04_x = 1;

	int except_wh_D_2 = 0, except_wh_B_2 = 0, except_wh_C_2 = 0;
	int except_bl_D_2 = 0, except_bl_C_2 = 0;
	
	for (int extend_x = 0; extend_x < rows_size / 2; extend_x++) {
		p02_x = extend_x;
		p03_x = extend_x + 1;
		p04_x = extend_x * 2 + 1;
		for (int extend_y = 0; extend_y < cols_size; extend_y++) {
			p02_y = extend_y;
			p04_y = extend_y;
			stop_move_y = p04_y;
			for (int movey = 0; stop_move_y < rows_size; movey++) {
				stop_move_x = p04_x;
				for (int movex = 0; stop_move_x < cols_size; movex++) {
					if (p01_x - 1 < 0 || p01_y - 1 < 0)
						except_wh_D_2 = 0;
					else
						except_wh_D_2 = array_integral[p01_y - 1][p01_x - 1];
					if (p01_x - 1 < 0)
						except_wh_B_2 = 0;
					else
						except_wh_B_2 = array_integral[p02_y][p01_x - 1];
					if (p01_y - 1 < 0)
						except_wh_C_2 = 0;
					else
						except_wh_C_2 = array_integral[p01_y - 1][p02_x];
					if (p03_y - 1 < 0) {
						except_bl_D_2 = 0;
						except_bl_C_2 = 0;
					}
					else {
						except_bl_D_2 = array_integral[p03_y - 1][p03_x - 1];
						except_bl_C_2 = array_integral[p03_y - 1][p04_x];
					}

					black = array_integral[p04_y][p04_x] - array_integral[p02_y][p02_x] - except_bl_C_2 + except_wh_C_2;
					white = array_integral[p02_y][p02_x] - except_wh_B_2 - except_wh_C_2 + except_wh_D_2;

					array_feature[counting] = abs(black - white);

					p01_x++;
					p02_x++;
					p03_x++;
					p04_x++;
					counting++;
					stop_move_x++;
				}
				p01_x = 0;
				p02_x = extend_x;
				p03_x = extend_x + 1;
				p04_x = extend_x * 2 + 1;
				p01_y++;
				p02_y++;
				p03_y++;
				p04_y++;
				stop_move_y++;
			}
			p01_y = 0;
			p03_y = 0;
		}
	}
	feature_numbers = counting;
}

int feature_detecting::output_feature_numbers() {
	return feature_numbers;
}
