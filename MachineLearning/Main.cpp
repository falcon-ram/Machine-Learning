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
	nn->feedForward();
	nn->setErrors();
	nn->printToConsole();

	vector<double> errors = nn->getErrors();
	for (size_t i = 0; i < errors.size(); i++)
	{
		cout << "Error " << i << " : " << errors.at(i) << endl;
	}
	cout << endl;
	cout << "Total error: " << nn->getTotalError() << endl;

	return 0;
}