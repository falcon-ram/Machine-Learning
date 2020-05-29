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

void Network::setCurrentTarget(vector<double> target)
{
	this->target = target;
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

void Network::backPropagation()
{
	vector<Matrix*> newWeights;
	Matrix* gradient;

	// Ouput to hidden
	int outputLayerIndex = this->layers.size() - 1;
	Matrix* derivedValsYtoZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
	Matrix* gradientsYtoZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
	for (size_t i = 0; i < this->errors.size(); i++)
	{
		double d = derivedValsYtoZ->getValue(0, i);
		double e = this->errors.at(i);
		double g = d * e;
		gradientsYtoZ->setValue(0, i, g);
	}

	int lastHiddenLayerIndex = outputLayerIndex - 1;
	Layer* lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
	Matrix* weightsOutputToHidden = this->weightMatrices.at(outputLayerIndex - 1);
	Matrix* deltaOutputToHidden = (new utils::MultiplyMatrix(gradientsYtoZ->transpose(), lastHiddenLayer->matrixifyActivatedVals()))->execute()->transpose();

	Matrix* newWeightsOutputToHidden = new Matrix(*weightsOutputToHidden - *deltaOutputToHidden);
	newWeights.push_back(newWeightsOutputToHidden);
	gradient = new Matrix(gradientsYtoZ->getNumRows(), gradientsYtoZ->getNumCols(), false);
	for (int r = 0; r < gradient->getNumRows(); r++)
	{
		for (int c = 0; c < gradient->getNumCols(); c++)
		{
			gradient->setValue(r, c, gradientsYtoZ->getValue(r, c));
		}
	}

	// Moving from last hidden layer down to input layer
	for (int i = (outputLayerIndex-1); i > 0; i--)
	{
		Layer* l = this->layers.at(i);
		Matrix* derivedHidden = l->matrixifyDerivedVals();
		Matrix* activatedHidden = l->matrixifyActivatedVals();
		Matrix* derivedGradients = new Matrix(1, l->getNeurons().size(), false);
		Matrix* weightMatrix = this->weightMatrices.at(i);
		Matrix* originalWeight = this->weightMatrices.at(i - 1);

		for (int r = 0; r < weightMatrix->getNumRows(); r++)
		{
			double sum = 0;
			for (int c = 0; c < weightMatrix->getNumCols(); c++)
			{
				double p = gradient->getValue(0, c)* weightMatrix->getValue(r, c);
				sum += p;
			}
			double g = sum * activatedHidden->getValue(0, r);
			derivedGradients->setValue(0, r, g);
		}

		Matrix* leftNeurons;
		if ((i - 1) == 0)
		{
			leftNeurons = this->layers.at(i - 1)->matrixifyVals();
		}
		else {
			leftNeurons = this->layers.at(i - 1)->matrixifyActivatedVals();
		}
		Matrix* deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(), leftNeurons))->execute()->transpose();
		Matrix* newWeight = new Matrix(*originalWeight - *deltaWeights);
		
		gradient = new Matrix(derivedGradients->getNumRows(), derivedGradients->getNumCols(), false);
		for (int r = 0; r < gradient->getNumRows(); r++)
		{
			for (int c = 0; c < gradient->getNumCols(); c++)
			{
				gradient->setValue(r, c, derivedGradients->getValue(r, c));
			}
		}

		// Load up new matrices
		newWeights.push_back(newWeight);
	}

	// Delete old weights
	for (size_t i = 0; i < this->weightMatrices.size(); i++)
	{
		delete this->weightMatrices.at(i);
	}
	// Load new weights
	reverse(newWeights.begin(), newWeights.end());
	this->weightMatrices = newWeights;
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

void Network::setErrors()
{
	int outputLayerIndex = this->layers.size() - 1;
	double tempErr = 0.0;

	if (this->target.size() == 0)
	{
		cerr << "No target for this neural network\n";
		assert(false);
	}
	if (this->target.size() != this->layers.at(outputLayerIndex)->getNeurons().size())
	{
		cerr << "Target size is not the same as output layer size: " << this->layers.at(outputLayerIndex)->getNeurons().size() << endl;
		assert(false);
	}

	this->error = 0.0;
	this->errors.clear();
	vector<Neuron*>outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();
	for (size_t i = 0; i < target.size(); i++)
	{
		tempErr = (outputNeurons.at(i)->getActivatedVal() - target.at(i));

		errors.push_back(tempErr);
		this->error += pow(tempErr,2);
	}
	this->error = 0.5 * this->error;
	historicalerrors.push_back(this->error);
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

void Network::printInputToConsole()
{
	for (size_t i = 0; i < this->input.size(); i++)
	{
		cout << this->input.at(i) << "\t";
	}
	cout << endl;
}

void Network::printOutputToConsole()
{
	int indexOfOutputLayer = this->layers.size() - 1;
	Matrix* outputValues = this->layers.at(indexOfOutputLayer)->matrixifyActivatedVals();
	for (int c = 0; c < outputValues->getNumCols(); c++)
	{
		cout << outputValues->getValue(0, c) << "\t";
	}
	cout << endl;
}

void Network::printTargetToConsole()
{
	for (size_t i = 0; i < this->target.size(); i++)
	{
		cout << this->target.at(i) << "\t";
	}
	cout << endl;
}
