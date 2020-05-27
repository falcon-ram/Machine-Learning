#pragma once
#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
using namespace std;

class Neuron
{
public:
	// Constructor
	Neuron(double val);

	// Fast Sigmoid function
	// f(x) = x / (1 + |x|)
	void activate();

	// Derivative for fast sigmoid function
	// f'(x) = f(x) * (1 - f(x))
	void derive();

	// Setter
	void setVal(double val);

	// Getter
	double getVal() { return this->val; }
	double getActivatedVal() { return this->activatedVal; }
	double getDerivedVal() { return this->derivedVal; }

private:
	// Raw value
	double val;

	// Value after applying the activation function
	double activatedVal;

	// The approximate derivative of the activated val
	double derivedVal;
};
#endif // !_NEURON_HPP_
