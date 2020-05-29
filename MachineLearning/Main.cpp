// Machine learning tutorial from:
// https://www.youtube.com/watch?v=PQo78WNGiow&list=PL2-7U6BzddIYBOl98DDsmpXiTcj1ojgJG
// Live Coding 2: C++ Neural Network
// - devlogs
#include <iostream>
#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"
#include "Network.h"

using namespace std;

int main(int argc, char** argv) {
	vector<double> input{ 1,0,1 };
	vector<int> topology{ 3,2,3 }; // 3 neurons input, 2 neurons hidden, 1 neuron output

	Network* nn = new Network(topology);
	nn->setCurrentInput(input);
	nn->setCurrentTarget(input);
	
	// Training process
	for (int i = 0; i < 1000; i++)
	{
		cout << "Epoch: " << i << endl;
		nn->feedForward();
		nn->setErrors();
		cout << "Total error: " << nn->getTotalError() << endl;
		nn->backPropagation();

		cout << "===================" << endl;
		cout << "OUTPUT: ";
		nn->printOutputToConsole();
		cout << "TARGET: ";
		nn->printTargetToConsole();
		cout << "===================" << endl;
		cout << endl;
	}

	return 0;
}