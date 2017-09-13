#pragma once

template <class T>
class results
{
public:
	double *Et;//
	int *t_point_t;
	int *p_value_t;
	double *threshold_t;
	int *correct;
	int Tt_training;
	results(int Tt_training) {
		this->Tt_training = Tt_training;
		Et = new double[Tt_training];
		t_point_t = new int[Tt_training];
		p_value_t = new int[Tt_training];
		threshold_t = new double[Tt_training];
		correct = new int[Tt_training];
	}
	~results() {
		//delete Et;
		//delete t_point_t;
		//delete p_value_t;
		//delete threshold_t;
		//delete correct;
	}
	void output_all_result() {
		cout << "Et\t" << "T_point\t" << "P_value\t" << "Threshold\t" << "correct\t" << endl;
		for (int n = 0; n < Tt_training; n++) {
			cout << Et[n] << "\t" << t_point_t[n] << "\t" << p_value_t[n] << "\t" << threshold_t[n] << "\t" << correct[n] << endl;
		}
	}

	T output_Et() {
		return Et;
	}

	int output_p(int i) {
		return t_point_t[i];
	}

private:

};