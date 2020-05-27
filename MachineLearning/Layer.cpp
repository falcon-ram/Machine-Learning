#include "Layer.h"

Layer::Layer(int size)
{
	this->size = size;
	for (int i = 0; i < this->size; i++)
	{
		Neuron* n = new Neuron(0.0);
		this->neurons.push_back(n);
	}
}

void Layer::setValue(int neuron, double val)
{
	this->neurons.at(neuron)->setVal(val);
}

vector<Neuron*> Layer::getNeurons()
{
	return neurons;
}

Matrix* Layer::matrixifyVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (unsigned int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getVal());
	}
	return m;
}

Matrix* Layer::matrixifyActivatedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (unsigned int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getActivatedVal());
	}
	return m;
}

Matrix* Layer::matrixifyDerivedVals()
{
	Matrix* m = new Matrix(1, this->neurons.size(), false);
	for (unsigned int i = 0; i < this->neurons.size(); i++)
	{
		m->setValue(0, i, this->neurons.at(i)->getDerivedVal());
	}
	return m;
}
