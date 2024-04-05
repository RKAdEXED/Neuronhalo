#pragma once
#include "Neuron.h"
#include <vector>

class Reteg
{
private:
	std::vector<Neuron> reteg;
public:
	Reteg(int magassag);
	Reteg(int magassag, std::vector<double> values);
	size_t getsize() { return reteg.size(); }
	Neuron& getNeuron(int i) { return reteg[i]; }
	Neuron* getNeuron_ptr(int i) {	return &reteg[i];	}
	void setkovireteginputs();
	void activation();
	void setInitval(std::vector<double> ujbemenet);
	double getvalue(int index) { return reteg[index].getvalue(); }
	void reteg_backprop(double learning_rate, double target);
};

