#include "Network.h"

Network::Network(vector<int> topology)
{
	this->topology = topology;
	this->topologySize = topology.size();
	for (int i = 0; i < topologySize; i++)
	{
		Layer* l = new Layer(topology.at(i));
		this->layers.push_back(l);
	}

	for (int i = 0; i < (topologySize-1); i++)
	{
		Matrix* m = new Matrix(topology.at(i), topology.at(i + 1), true);
		this->weightMatrices.push_back(m);
	}
}

void Network::setCurrentInput(vector<double> input)
{
	this->input = input;

	for (unsigned int i = 0; i < input.size(); i++)
	{
		this->layers.at(0)->setValue(i, input.at(i));
	}
}

void Network::feedForward()
{
	for (unsigned int i = 0; i < (this->layers.size() - 1); i++)
	{
		Matrix* a; 
		if (i == 0)
		{
			a = this->getNeuronMatrix(i);
		}
		else {
			a = this->getActivatedNeuronMatrix(i);
		}

		Matrix* b = this->getWeightMatrix(i);
		Matrix* c = (new utils::MultiplyMatrix(a, b))->execute();

		for (int c_index = 0; c_index < c->getNumCols(); c_index++)
		{
			this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index)); // Set neuron values of the next layer
		}

	}
}

void Network::printToConsole()
{
	for (unsigned int i = 0; i < this->layers.size(); i++)
	{
		cout << "Layer: " << i << endl;
		if (i == 0)
		{
			Matrix* m = this->layers.at(i)->matrixifyVals();
			m->printToConsole();
		}
		else {
			Matrix* m = this->layers.at(i)->matrixifyActivatedVals();
			m->printToConsole();
		}
		// Print Weighted matrix
		if (i < (this->layers.size() - 1))
		{
			cout << "======================\n";
			cout << "Weight matrix: " << i << endl;
			Matrix* m = this->getWeightMatrix(i);
			m->printToConsole();
			cout << "======================\n";
		}
	}
}

Matrix* Network::getNeuronMatrix(int index)
{
	return this->layers.at(index)->matrixifyVals();
}

Matrix* Network::getActivatedNeuronMatrix(int index)
{
	return this->layers.at(index)->matrixifyActivatedVals();
}

Matrix* Network::getDerivedNeuronMatrix(int index)
{
	return this->layers.at(index)->matrixifyDerivedVals();
}

Matrix* Network::getWeightMatrix(int index)
{
	return this->weightMatrices.at(index);
}

void Network::setNeuronValue(int indexLayer, int indexNeuron, double val)
{
	this->layers.at(indexLayer)->setValue(indexNeuron, val);
}