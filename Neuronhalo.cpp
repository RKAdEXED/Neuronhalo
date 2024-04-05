#include "Neuronhalo.h"

Neuronhalo::Neuronhalo(int hossz, int* meretek) {
	for (int i = 0; i < hossz; i++) {
		Reteg uj(meretek[i]);
		osszekot(uj);
	}
}

Neuronhalo::Neuronhalo(int hossz, std::vector<double> init_val) {
	Reteg ujab(init_val.size(), init_val);
	osszekot(ujab);
	for (int i = 1; i < hossz - 1; i++) {
		Reteg uj(init_val.size()/6);
		osszekot(uj);
	}
	Reteg uj(10);
	osszekot(uj);
	//vart_kimenet = exp_output;
}

Neuronhalo::Neuronhalo(Reteg uj) {
	osszekot(uj);
}

void Neuronhalo::osszekot(Reteg uj) {
	halo.push_back(uj);
	if (halo.size() != 1) {
		for (size_t i = 0; i < halo.at(halo.size() - 2).getsize(); i++) {
			for (size_t j = 0; j < halo.at(halo.size() - 1).getsize(); j++) {
				Neuron& beallit = halo[halo.size() - 2].getNeuron(i);
				Neuron* erre = halo[halo.size() - 1].getNeuron_ptr(j);
				beallit.init_kovi(erre);
			}
		}
	}
}

void Neuronhalo::setosztalynev(const char* be, int hanyadik) {
	Neuron& osztalyoz = halo.at(halo.size() - 1).getNeuron(hanyadik);
	osztalyoz.setnev(be);
}

const char* Neuronhalo::legnagyobb() {
	double legnagyobb = std::numeric_limits<double>::lowest();;
	size_t index = 0;
	for (size_t i = 0; i < halo.back().getsize(); i++) {
		if (halo.back().getvalue(i) > legnagyobb) {
			index = i;
			legnagyobb = halo.back().getvalue(i);
		}
	}
	return halo.back().getNeuron(index).getnev();
}

void Neuronhalo::futtat() {
	for (size_t i = 1; i < halo.size(); i++) {
		halo[i - 1].setkovireteginputs();
		halo[i].activation();
	}
}

double Neuronhalo::cost(size_t which_layer) {
	double vissza = 0;
	std::cout << std::endl;
	for (size_t i = 0; i < halo[which_layer].getsize(); i++) {
		double supposed_output;
		if (vart_kimenet == i) {
			supposed_output = 1;
		}
		else {
			supposed_output = 0;
		}
		std::cout << halo[which_layer].getvalue(i) << " supp "<< std::endl;
		vissza += ((halo[which_layer].getvalue(i) - supposed_output) * ((halo[which_layer].getvalue(i) - supposed_output)));
	}
	return vissza;
}

void Neuronhalo::backprop(double learning_rate, int target) {
	double Dtarget = double(target);
	for (size_t i = halo.size() - 1; i != 0; i--) {
		std::cout << " backp " << std::endl;
		halo[i].reteg_backprop(learning_rate, Dtarget);
	}
}


void Neuronhalo::ujBement(std::vector<double> ujbemenet) {
	halo[0].setInitval(ujbemenet);
}