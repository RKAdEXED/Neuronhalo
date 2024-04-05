#pragma once
#include "Reteg.h"
#include <iostream>
#include <vector>
#include <math.h>

class Neuronhalo
{
private:
	std::vector<Reteg> halo;
	int meret;
	std::vector<double> bemenet;
	int vart_kimenet;
public:
	Neuronhalo(int hossz, int* meretek);
	Neuronhalo(int hossz, std::vector<double> init_val);
	Neuronhalo(Reteg uj);
	void osszekot(Reteg uj);
	void setVart(int szam) { vart_kimenet = szam; }
	void setBemenet(double asd) { bemenet.push_back(asd); }
	void setBemenet(std::vector<double> ujbemenet) { bemenet = ujbemenet; }
	void ujBement(std::vector<double> ujbemenet);
	void setosztalynev(const char* be, int hanyadik);
	void futtat();
	const char* legnagyobb();
	double cost(size_t which_layer);
	std::vector<Reteg> gethalo()const { 
		/*for (auto it = halo.begin(); it < halo.end(); it++) {
			Reteg x = *it;
		}
		for (Reteg x : halo) {
			x
		}*/
		return halo; }
	void backprop(double learning_rate, int target);
	int getT() const { return vart_kimenet; }
};

