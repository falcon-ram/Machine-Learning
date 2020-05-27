#pragma once
#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Matrix.h"

using namespace std;

class Layer
{
public:
	// Constructor
	Layer(int size);
	void setValue(int neuron, double val);
	vector<Neuron*> getNeurons();

	Matrix *matrixifyVals();
	Matrix *matrixifyActivatedVals();
	Matrix *matrixifyDerivedVals();

private:
	int size;

	vector<Neuron*> neurons;
	
};
#endif // !_LAYER_HPP_