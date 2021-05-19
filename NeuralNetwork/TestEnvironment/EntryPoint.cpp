#include <iostream>
#include <time.h>
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
	return (vals[1] < vals[0] ? vals[1] - vals[0] : vals[0] - vals[1]);
}

float FastSigmoid(float x)
{
	return x / (1.0f + fabs(x));
}

int main()
{
	srand(time(0));
	//Neuron mainNeuron(TempTest);
	//Neuron testNeuron;
	//testNeuron.output = 5;
	//mainNeuron.AddInput(&testNeuron);
	//mainNeuron.Calculate();
	//std::cout << std::to_string(mainNeuron.output) << std::endl;

	TestDLL();

	NeuralNetwork* brain = new NeuralNetwork({ 4, 4, 1 }, true/*, FastSigmoid*/);

	float myPosX = 0;
	float myPosY = 0;

	//std::vector<std::vector<float>> = {{3,4},{},{},{}}

	float targetPosX = 3;
	float targetPosY = 4;
	float targetVal = (float)sqrt(pow(targetPosX, 2) + pow(targetPosY, 2));

	std::vector<float*> testInputs = { &myPosX, &myPosY, &targetPosX, &targetPosY };
	brain->SetInputs(testInputs);

	GeneticAlgorithm genePool;

	genePool.instanceCount = 100;

	genePool.originalNetwork = brain;

	genePool.CreateFirstGen();

	genePool.CompletelyRandomiseWeights(-10, 10);

	genePool.fitnessFunc = TestFitFunc;

	genePool.breedersCount = 30;

	genePool.generationalVariance = 0.01f;

	int i = 0;
	while (i < 100)
	{

		for (int i = 0; i < testSets.size(); i++)
		{

		}
		genePool.Update();

		std::vector<std::vector<float>> outputs;

		for (int i = 0; i < genePool.instanceCount; i++)
		{
			std::vector<float> out = { genePool.instances[i].GetOutputs()[0], targetVal };
			outputs.push_back(out);
			std::cout << "brain # " << i << /*" with an ID of:" << genePool.instances[i].ID <<*/ " thinks the distance is: " << std::to_string(genePool.instances[i].GetOutputs()[0]) << " | Target val: " << std::to_string(targetVal) << std::endl;
		}
		std::cout << std::endl;

		genePool.RunGenerationalGuantlet(outputs);
		genePool.CreateNewGen();
		i++;
	}
	//-------
	genePool.Update();
	std::vector<std::vector<float>> outputs;
	for (int i = 0; i < genePool.instanceCount; i++)
	{
		std::vector<float> out = { genePool.instances[i].GetOutputs()[0], 5 };
		outputs.push_back(out);
		std::cout << "brain # " << i << " thinks the distance is: " << std::to_string(genePool.instances[i].GetOutputs()[0]) << std::endl;
	}
	std::cout << std::endl;
	genePool.RunGenerationalGuantlet(outputs);
	std::cout << "best value: " << std::to_string(genePool.nextGenProgenitors[0].GetOutputs()[0]) << std::endl;
	std::cout << "target value: " << std::to_string(targetVal) << std::endl;
	//-------

	return 0;
}