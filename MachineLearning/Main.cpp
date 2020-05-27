#include <iostream>
#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"
#include "Network.h"

using namespace std;

int main(int argc, char** argv) {
	vector<double> input{ 1,0,1 };
	vector<int> topology{ 3,2,1 }; // 3 neurons input, 2 neurons hidden, 1 neuron output

	Network* nn = new Network(topology);
	nn->setCurrentInput(input);
	nn->feedForward();
	nn->printToConsole();

	return 0;
}