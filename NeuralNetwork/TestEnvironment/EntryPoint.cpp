#include <iostream>
#include <string>

#include "Test.h"
#include "Neuron.h"

float TempTest(float in)
{
	return in * 10;
}

int main()
{
	Neuron mainNeuron(TempTest);
	Neuron testNeuron;
	testNeuron.output = 5;
	mainNeuron.AddInput(&testNeuron);
	mainNeuron.Calculate();
	std::cout << std::to_string(mainNeuron.output);

	return 0;
}