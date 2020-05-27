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
	void feedForward();
	void printToConsole();

	Matrix* getNeuronMatrix(int index);
	Matrix* getActivatedNeuronMatrix(int index);
	Matrix* getDerivedNeuronMatrix(int index);
	Matrix* getWeightMatrix(int index);

	void setNeuronValue(int indexLayer, int indexNeuron, double val);

private:
	int topologySize;

	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weightMatrices;
	vector<double> input;
};
#endif // !_NETWORK_HPP_
