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

float GetFloatTextInput()
{
	std::string input;
	std::getline(std::cin, input);
	return std::stof(input);
}

int main()
{
	srand(time(0));

	TestDLL();

	std::string mode;
	while (true)
	{
		std::cout << "\"learn\" or \"test\"?" << std::endl;
		std::getline(std::cin, mode);
		for (int i = 0; i < mode.size(); i++)
		{
			if (std::isalpha(mode[i]))
			{
				mode[i] = tolower(mode[i]);
			}
		}
		if ((mode == "learn") || (mode == "test"))
		{
			break;
		}
	}

	if (mode == "learn")
	{
		NeuralNetwork* brain = new NeuralNetwork({4, 4, 1 }, true);

		std::vector<std::vector<float>> testSets =
		{
		{5, 2, -3.024f, -1},
		{0, 0, 48.4f, -23},
		{-10, -3, -5, -1}, 
		{-12, -5, -1.5f, 34}, 
		{54.3f, 78, -45.6f, 76}, 
		{-8.3f, 3, 9.93f, -8}, 
		{-2.2f, 19, 3.5f, 16}, 
		{1.854f, 85.2f, -25, -80}, 
		{84, 6, -1, 4.21f}, 
		{2.45f, -12.3f, 45, 90}, 
		{95, 123.42f, -242, 65.432f},
		{3.4f, -6.7f, 33, -9.8f}
		};

		float myPosX = 0;
		float myPosY = 0;
		float targetPosX = 3;
		float targetPosY = 4;
		float targetVal = (float)sqrt(pow(targetPosX - myPosX, 2) + pow(targetPosY - myPosY, 2));

		std::vector<float*> testInputs = { &myPosX, &myPosY, &targetPosX, &targetPosY };
		brain->SetInputs(testInputs);

		GeneticAlgorithm genePool;

		genePool.instanceCount = 1000;

		genePool.originalNetwork = brain;

		genePool.CreateFirstGen();

		genePool.CompletelyRandomiseWeights(-10, 10);

		genePool.fitnessFunc = TestFitFunc;

		genePool.breedersCount = 300;

		genePool.generationalVariance = 1;

		int j = 0;
		int generationCount = 4000;
		while (j < generationCount)
		{
			std::vector<float> results(genePool.instanceCount);
			float target = 0;

			for (int i = 0; i < testSets.size(); i++)
			{
				results[i] = 0;
				myPosX = testSets[i][0];
				myPosY = testSets[i][1];
				targetPosX = testSets[i][2];
				targetPosY = testSets[i][3];
				float xDiff = myPosX - targetPosX;
				float yDiff = myPosY - targetPosY;
				targetVal = (float)sqrt(xDiff * xDiff + yDiff * yDiff);
				//target += targetVal;

				//brain->SetInputs(testInputs);

				for (int k = 0; k < genePool.instanceCount; k++)
				{
					genePool.instances[k].SetInputs(testInputs);
				}
				genePool.Update();
				for (int k = 0; k < genePool.instanceCount; k++)
				{
					float actualVal = genePool.instances[k].GetOutputs()[0];
					results[k] += std::abs(actualVal - targetVal);
				}
			}
			std::vector<std::vector<float>> outputs;
			float averageFitness = 0;
			for (int i = 0; i < genePool.instanceCount; i++)
			{
				outputs.push_back({ results[i], 0 });
				averageFitness += results[i];
				//std::cout << "brain # " << i << " thinks the sum of the distances are: " << outputs[i][0] << " | Target val: " << std::to_string(target) << std::endl;
			}
			std::cout << "Average fitness " << averageFitness / genePool.instanceCount;
			std::cout << std::endl;

			genePool.RunGenerationalGuantlet(outputs);
			if (j < generationCount - 1)
			{
				genePool.CreateNewGen();
			}
			j++;
		}

		genePool.nextGenProgenitors[0].Save("testPotato.dat");
	}
	else
	{
		bool shouldTest = true;
		while (shouldTest)
		{
			NeuralNetwork brain;
			brain = brain.Load("testPotato.dat");
			brain.Saturate();
			float ax = 0;
			float ay = 0;
			float bx = 0;
			float by = 0;

			std::cout << "Enter point A's X pos" << std::endl;
			ax = GetFloatTextInput();
			std::cout << "Enter point A's Y pos" << std::endl;
			ay = GetFloatTextInput();
			std::cout << "Enter point B's X pos" << std::endl;
			bx = GetFloatTextInput();
			std::cout << "Enter point B's Y pos" << std::endl;
			by = GetFloatTextInput();

			brain.SetInputs({ &ax, &ay, &bx, &by });

			brain.Update();

			std::cout << brain.GetOutputs()[0] << std::endl;
			std::cout << std::endl << "Input another set of values?" << std::endl;
			while (true)
			{
				std::cout << "\"y\" or \"n\"?" << std::endl;
				std::getline(std::cin, mode);
				for (int i = 0; i < mode.size(); i++)
				{
					if (std::isalpha(mode[i]))
					{
						mode[i] = tolower(mode[i]);
					}
				}
				if (mode == "y")
				{
					break;
				}
				else if (mode == "n")
				{
					shouldTest = false;
					break;
				}
			}
		}
	}

	//-------

	return 0;
}