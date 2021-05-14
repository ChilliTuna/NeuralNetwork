#include <iostream>
#include <string>

#include "Test.h"
#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"

float TempTest(float in)
{
	return in * 10;
}

float TestFitFunc(std::vector<float> vals)
{
	return vals[0] / vals[1];
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

	NeuralNetwork* brain = new NeuralNetwork({ 4, 4, 1 });

	float myPosX = 0;
	float myPosY = 0;
	float targetPosX = 3;
	float targetPosY = 4;

	std::vector<float*> testInputs = { &myPosX, &myPosY, &targetPosX, &targetPosY };
	brain->SetInputs(testInputs);

	GeneticAlgorithm genePool;

	genePool.originalNetwork = brain;

	genePool.CreateFirstGen();

	genePool.CompletelyRandomiseWeights(-10, 10);

	genePool.fitnessFunc = TestFitFunc;

	while (true)
	{
		char string[10];
		std::cin >> string;

		genePool.Update();

		std::vector<std::vector<float>> outputs;
		
		for (int i = 0; i < genePool.instanceCount; i++)
		{
			std::vector<float> out = { genePool.instances[i].GetOutputs()[0], 5 };
			outputs.push_back(out);
			std::cout << "brain # " << i << " thinks the distance is: " << std::to_string(genePool.instances[i].GetOutputs()[0]) << std::endl;
		}

		genePool.RunGenerationalGuantlet(outputs);
		genePool.CreateNewGen();
	}
	return 0;
}