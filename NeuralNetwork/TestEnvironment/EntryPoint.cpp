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
	return (vals[1] < vals[0] ? vals[0] - vals[1] : vals[1] - vals[0]);
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

	std::vector<std::vector<float>> testSets = { {3,4}, {6, 8}, {12, 16} };

	float targetPosX = 3;
	float targetPosY = 4;
	float targetVal = (float)sqrt(pow(targetPosX, 2) + pow(targetPosY, 2));

	std::vector<float*> testInputs = { &myPosX, &myPosY, &targetPosX, &targetPosY };
	brain->SetInputs(testInputs);

	GeneticAlgorithm genePool;

	genePool.instanceCount = 50;

	genePool.originalNetwork = brain;

	genePool.CreateFirstGen();

	genePool.CompletelyRandomiseWeights(-10, 10);

	genePool.fitnessFunc = TestFitFunc;

	genePool.breedersCount = 5;

	genePool.generationalVariance = 0.01f;

	int j = 0;
	while (j < 10)
	{
		std::vector<float> results(genePool.instanceCount);
		float target = 0;
		for (int i = 0; i < testSets.size(); i++)
		{
			targetPosX = testSets[i][0];
			targetPosY = testSets[i][1];
			brain->SetInputs(testInputs);
			targetVal = (float)sqrt(pow(targetPosX, 2) + pow(targetPosY, 2));
			target += targetVal;

			genePool.Update();

			for (int i = 0; i < genePool.instanceCount; i++)
			{
				results[i] += genePool.instances[i].GetOutputs()[0];
			}
		}
		std::vector<std::vector<float>> outputs;
		for (int i = 0; i < genePool.instanceCount; i++)
		{
			outputs.push_back({ results[i], target });
			std::cout << "brain # " << i << " thinks the sum of the distances are: " << outputs[i][0] << " | Target val: " << std::to_string(target) << std::endl;
		}
		std::cout << std::endl;

		genePool.RunGenerationalGuantlet(outputs);
		if (j < 199)
		{
			genePool.CreateNewGen();
		}
		j++;
	}

	genePool.nextGenProgenitors[0].Save("testPotato.dat");

	//-------

	return 0;
}