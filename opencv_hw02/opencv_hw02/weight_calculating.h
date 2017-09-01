#pragma once
#include "database.h"
#include "detect_correct_wrong_table.h"
#include <math.h>

class weight_calculating
{
public:
	weight_calculating(int, int, int, database<int> *);
	~weight_calculating();
	double weight_initualize(int);
	void weight_calculating_process(detect_correct_wrong_table<int> *, int, double);
	void balance_weight_initualize();
private:
	int picture_nums = 0;
	int human_face = 0, non_human_face = 0;
	database<int> *data;
};

