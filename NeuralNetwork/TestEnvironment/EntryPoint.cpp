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

	std::vector<std::vector<std::vector<float>>> weights = 
	{
		{{}},
		{{-1}, {1}}
	};


	TestDLL();

	NeuralNetwork brain({ 2, 1 });

	float myPos = 5;
	float targetPos = 3;

	std::vector<float*> testInputs = { &myPos, &targetPos };
	brain.SetInputs(testInputs);
	brain.SetWeights(weights);
	//brain[1][0]->ChangeWeight(brain[0][0], -1); 

	//weights[1][0][0] = -2.0f;
	//brain.SetWeights(weights);

	brain.Update();
	std::cout << "I need to move to the right by " << std::to_string(brain.GetOutputs()[0]) << std::endl;

	return 0;
}