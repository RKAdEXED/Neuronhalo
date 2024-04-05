#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

class Neuron;
struct Tobbi {
	double weights;
	Neuron* kovik;
};

class Neuron
{
private:
	std::vector<double> inputs;
	std::vector<Neuron*> elozok = { nullptr };
	std::vector<Tobbi> kovetkezok;
	double value;
	double bias;
	const char* osztaly;
public:
	Neuron();
	Neuron(double value) :value(value), bias(0) { osztaly = ""; };
	std::vector<Neuron*> getElozok();
	double relu(std::vector<double> be, double hitetlenkedes);
	double Derivalt_relu(double be, double eloitelet) { double out = be - eloitelet; if (out > 0) { return 1; } else { return 0; } }
	void setvalue(double be) { value = be; }
	void setinput(double uj_be);
	void init_kovi(Neuron* kovi);
	void setkovi_weight(double weight, Neuron* hova);
	void setnev(const char* nev) { osztaly = nev; }
	void addinputtokovi();
	void BackP(double learning_rate, double target);
	std::vector<double> getinputs();
	std::vector<Tobbi> getKovetkezok()const { return kovetkezok; }
	double getvalue() { return value; }
	double getbias() const { return bias; }
	double getweight(Neuron* be);
	void resetvalue() { value = 0; }
	void ujElozo(Neuron* be) { elozok.push_back(be); }
	const char* getnev() { return osztaly; }
};