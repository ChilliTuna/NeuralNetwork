#include <iostream>
#include <string>

#include "Test.h"
#include "Neuron.h"
#include "NeuralNetwork.h"

float TempTest(float in)
{
	return in * 10;
}

int main()
{
	//Neuron mainNeuron(TempTest);
	//Neuron testNeuron;
	//testNeuron.output = 5;
	//mainNeuron.AddInput(&testNeuron);
	//mainNeuron.Calculate();
	//std::cout << std::to_string(mainNeuron.output) << std::endl;

	TestDLL();

	NeuralNetwork brain;
	brain.defaultFunc = TempTest;
	brain.GenerateNetwork({ 1, 1 });

	std::vector<float> testInputs = { 78 };
	brain.SetInputs(testInputs);

	brain.Update();
	std::cout << std::to_string(brain.GetOutputs()[0]) << std::endl;

	return 0;
}