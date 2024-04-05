#include "Neuron.h"


Neuron::Neuron() {
	bias = 0;
	value = NULL;
	osztaly = "";
}
double Neuron::relu(std::vector<double> be, double hitetlenkedes)
{
	if (be.size() == 0) {
		return 0;
	}
	else {
		double osszeg = 0;
		for (size_t i = 0; i < be.size(); i++)
		{
			osszeg += be[i];
			//std::cout << be[i] << " input " << i << "-edik" << std::endl;
		}
		//std::cout << osszeg << " osszeg " << be.size() << " size " << std::endl;
		if (osszeg - hitetlenkedes > 0) {
			return osszeg/be.size();
		}
		else {
			//std::cout << " BIG ELSE " << std::endl;
			return 0;
		}
	}
}

void Neuron::setinput(double uj_be) {
	inputs.push_back(uj_be);
}

void Neuron::init_kovi(Neuron* kovi) {
	Tobbi uj;
	double random = ((double)rand() / (RAND_MAX));
	uj.weights = random;
	uj.kovik = kovi;
	kovetkezok.push_back(uj);
	kovetkezok[kovetkezok.size() - 1].kovik->ujElozo(this);
}
void Neuron::setkovi_weight(double weight, Neuron* hova) {
	if (kovetkezok.size() == 0) {
		throw "PKWSUX";
	}
	else {
		for (size_t i = 0; i < kovetkezok.size(); i++) {
			if (kovetkezok[i].kovik == hova) {
				kovetkezok[i].weights = weight;
				return;
			}
		}
	}
}

std::vector<Neuron*> Neuron::getElozok() {
	return elozok;
}


void Neuron::addinputtokovi() {
	if (kovetkezok.size() != 0) {
		for (size_t i = 0; i < kovetkezok.size(); i++) {
			double input_ertek = kovetkezok[i].weights * value;
			//std::cout << input_ertek << " uj input " << std::endl;
			kovetkezok[i].kovik->setinput(input_ertek);
		}
	}
}



std::vector<double> Neuron::getinputs() {
	if (inputs.size() == 0) {
		throw " NOGO no input ";
	}
	else { return inputs; }
}

double Neuron::getweight(Neuron* be) {
	for (size_t i = 0; i < getKovetkezok().size(); i++) {
		if (getKovetkezok().at(i).kovik == be) {
			return getKovetkezok().at(i).weights;
		}
	}
}

void Neuron::BackP(double learning_rate, double target){
	 if (elozok.size() != 0) {
		for (size_t i = 0; i < elozok.size(); i++) {
			if (elozok[i] != nullptr) {
				double cost = 2 * (elozok[i]->getvalue() - target);
				double suly = elozok[i]->getweight(this);
				double relu_out = Derivalt_relu(suly, getbias()); //ez egy x vagy 0 function amit deriválni kell tehát 0 vagy 1 lesz a relu_out
				double outWeight = cost * relu_out * elozok[i]->getvalue();
				double new_weight = elozok[i]->getweight(this) - learning_rate * outWeight;
				elozok[i]->setkovi_weight(new_weight, this);
			}
		}
	}
}