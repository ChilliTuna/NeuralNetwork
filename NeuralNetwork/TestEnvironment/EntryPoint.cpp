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
		NeuralNetwork* brain = new NeuralNetwork({ 4, 4, 1 }, true);

		std::vector<std::vector<float>> testSets = { {5, 2, -3.024f, -1}, {-8.3f, 3, 9.93f, -8}, {-2.2f, 19, 3.5f, 16}, {1.854, 85.2, -25, -80} };

		float myPosX = 0;
		float myPosY = 0;
		float targetPosX = 3;
		float targetPosY = 4;
		float targetVal = (float)sqrt(pow(targetPosX - myPosX, 2) + pow(targetPosY - myPosY, 2));

		std::vector<float*> testInputs = { &myPosX, &myPosY, &targetPosX, &targetPosY };
		brain->SetInputs(testInputs);

		GeneticAlgorithm genePool;

		genePool.instanceCount = 50;

		genePool.originalNetwork = brain;

		genePool.CreateFirstGen();

		genePool.CompletelyRandomiseWeights(-10, 10);

		genePool.fitnessFunc = TestFitFunc;

		genePool.breedersCount = 5;

		genePool.generationalVariance = 0.001f;

		int j = 0;
		while (j < 1000)
		{
			std::vector<float> results(genePool.instanceCount);
			float target = 0;
			for (int i = 0; i < testSets.size(); i++)
			{
				myPosX = testSets[i][0];
				myPosY = testSets[i][1];
				targetPosX = testSets[i][2];
				targetPosY = testSets[i][3];
				brain->SetInputs(testInputs);
				targetVal = (float)sqrt(pow(targetPosX - myPosX, 2) + pow(targetPosY - myPosY, 2));
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