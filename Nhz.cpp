 // Nhz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include "Neuronhalo.h"
int main()
{
        srand(time(NULL));

        // Open the file
        std::ifstream file("train.csv");

        // Check if the file is open
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return 1; // Exit with error
        }

        std::string line;
        std::getline(file, line);
        std::getline(file, line); // Skip the first line (header)

        std::istringstream sor(line);
        std::string token;
        std::getline(sor, token, ','); // Read vart_kimenet
        int vart_kimenet = std::stol(token);
        std::vector<double> init_vals;
        while (std::getline(sor, token, ',')) {
            double val = std::stod(token);
            init_vals.push_back(val/255);
        }
        Neuronhalo yolo(5, init_vals);
        yolo.setosztalynev("nulla", 0);
        yolo.setosztalynev("egy", 1);
        yolo.setosztalynev("ketto", 2);
        yolo.setosztalynev("harom", 3);
        yolo.setosztalynev("negy", 4);
        yolo.setosztalynev("ot", 5);
        yolo.setosztalynev("hat", 6);
        yolo.setosztalynev("het", 7);
        yolo.setosztalynev("nyolc", 8);
        yolo.setosztalynev("kilenc", 9);
        while (std::getline(file, line)) {
            yolo.futtat();
            yolo.backprop(0.23, yolo.getT());
            std::istringstream iss(line);
            std::getline(iss, token, ','); // Read vart_kimenet
            int vart_kimenet = std::stoi(token);
            std::vector<double> new_vals;
            while (std::getline(iss, token, ',')) {
                double val = std::stod(token);
                new_vals.push_back(val/255);
            }
            yolo.ujBement(new_vals);
            std::cout << yolo.legnagyobb() << " hehe: ";
            std::cout << yolo.cost(yolo.gethalo().size() - 1) << " hihi " << std::endl;
        }

        std::cout << "Hello World!\n";
        return 0;
}
