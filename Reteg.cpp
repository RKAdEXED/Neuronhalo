#include "Reteg.h"

Reteg::Reteg(int magassag) {
	for (int i = 0; i < magassag; i++) {
		reteg.push_back(Neuron());
	}
}

Reteg::Reteg(int magassag, std::vector<double> values) {
	for (int i = 0; i < magassag; i++) {
		reteg.push_back(Neuron(values.at(i)));
	}
}

void Reteg::setkovireteginputs() {
	for (size_t i = 0; i < reteg.size(); i++) {
		reteg[i].addinputtokovi();
	}
}

void Reteg::activation() {
	for (size_t i = 0; i < reteg.size(); i++) {
		if (reteg[i].getinputs().size() != NULL) {
			reteg[i].setvalue(reteg[i].relu(reteg[i].getinputs(), reteg[i].getbias()));
			//std::cout << reteg[i].getvalue()<<" set inputs ";
			reteg[i].getinputs().clear();
		}
	}
	//std::cout << " ez volt " << std::endl;
}

void Reteg::reteg_backprop(double learning_rate, double target) {
	for (int i = 0; i < reteg.size(); i++) {
		if (reteg[i].getKovetkezok().size() == 0) {
			if (i == int(target)) {
				reteg[i].BackP(learning_rate, 1);
			}
			else {
				reteg[i].BackP(learning_rate, 0);
			}
		}
		else {
			reteg[i].BackP(learning_rate, reteg[i].getvalue());
		}
	}  
}

void Reteg::setInitval(std::vector<double> ujbemenet) {
	int i = 0;
	for (Neuron x : reteg) {
		x.setvalue(ujbemenet[i++]);
	}
}