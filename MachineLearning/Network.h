#pragma once
#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Layer.h"
#include "MultiplyMatrix.h"

using namespace std;

class Network
{
public:
	Network(vector<int> topology);
	void setCurrentInput(vector<double> input);
	void setCurrentTarget(vector<double> target);
	void feedForward();
	void printToConsole();
	void setErrors();

	Matrix* getNeuronMatrix(int index);
	Matrix* getActivatedNeuronMatrix(int index);
	Matrix* getDerivedNeuronMatrix(int index);
	Matrix* getWeightMatrix(int index);

	void setNeuronValue(int indexLayer, int indexNeuron, double val);

	double getTotalError() { return this->error; }
	vector<double> getErrors() { return this->errors; }

private:
	int topologySize;

	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weightMatrices;
	vector<double> input;
	vector<double> target;
	double error;
	vector<double> errors;
	vector<double> historicalerrors;
};
#endif // !_NETWORK_HPP_
