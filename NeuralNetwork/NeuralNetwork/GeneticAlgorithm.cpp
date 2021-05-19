#include "GeneticAlgorithm.h"
#include <iostream>
GeneticAlgorithm::GeneticAlgorithm()
{
	std::random_device rd;
	std::cout << rd() << "  " << rd() << std::endl;
	engine = std::mt19937(rd());
	std::uniform_real_distribution<float> distribution(-1, 1);
	
	
}

void GeneticAlgorithm::CreateFirstGen()
{
	generationCount = 1;
	for (int i = 0; i < instanceCount; i++)
	{
		instances.push_back(*originalNetwork);
		instances[i].Saturate();
	}
}

void GeneticAlgorithm::CreateNewGen()
{
	instances.clear();
	for (int i = 0; i < breedersCount; i++)
	{
		for (int j = 0; j < instanceCount / breedersCount; j++)
		{
			if (instances.size() < instanceCount)
			{
				instances.push_back(nextGenProgenitors[i]);
			}
		}
	}
	while(instances.size() < instanceCount)
	{
		instances.push_back(nextGenProgenitors[0]);
	}
	for (int i = 0; i < instanceCount; i++)
	{
		instances[i].Saturate();
	}
	RandomiseAllWeights(generationalVariance / 2 - generationalVariance, generationalVariance / 2);
	generationCount++;
}

void GeneticAlgorithm::RandomiseWeights(NeuralNetwork* instanceToModify, float negGeneticDif, float posGeneticDif)
{
	std::uniform_real_distribution<float> distribution(negGeneticDif, posGeneticDif);
	for (int i = 0; i < instanceToModify->network.size(); i++)
	{
		for (int j = 0; j < instanceToModify->network[i].size(); j++)
		{
			for (int k = 0; k < instanceToModify->network[i][j].GetWeightsCount(); k++)
			{
				instanceToModify->network[i][j].ChangeWeight(k, instanceToModify->network[i][j].GetWeight(k) + distribution(engine));
			}
		}
	}
}

void GeneticAlgorithm::RandomiseAllWeights(float negGeneticDif, float posGeneticDif)
{
	for (int i = 0; i < instances.size(); i++)
	{
		RandomiseWeights(&instances[i], negGeneticDif, posGeneticDif);
	}
}

void GeneticAlgorithm::CompletelyRandomiseWeights(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	for (int i = 0; i < instances.size(); i++)
	{
		for (int j = 0; j < instances[i].network.size(); j++)
		{
			for (int k = 0; k < instances[i].network[j].size(); k++)
			{
				for (int l = 0; l < instances[i].network[j][k].GetWeightsCount(); l++)
				{
					instances[i].network[j][k].ChangeWeight(l, instances[i].network[j][k].GetWeight(l) + distribution(engine));
				}
			}
		}
	}
}

//Checks the fitness of all NeuralNetworks in this genetic algorithm, the order of checkVals should match the order of their respective networks in the instances vector
void GeneticAlgorithm::RunGenerationalGuantlet(std::vector<std::vector<float>> checkVals)
{
	RunFitnessFunc(checkVals);
	std::vector<NeuralNetwork*> order;
	for (int i = 0; i < instanceCount; i++)
	{
		order.push_back(&instances[i]);
	}
	std::sort(order.begin(), order.end(), [](NeuralNetwork* a, NeuralNetwork* b) {return a->fitness > b->fitness; });
	nextGenProgenitors.clear();
	for (int i = 0; i < breedersCount; i++)
	{
		nextGenProgenitors.push_back(*order[i]);
	}
}

void GeneticAlgorithm::RunFitnessFunc(std::vector<std::vector<float>> checkVals)
{
	for (int i = 0; i < instanceCount; i++)
	{
		if (i < checkVals.size())
		{
			instances[i].fitness = fitnessFunc(checkVals[i]);
		}
		else
		{
			instances[i].fitness = 0;
		}
	}
}

void GeneticAlgorithm::Update()
{
	for (int i = 0; i < instanceCount; i++)
	{
		instances[i].Update();
	}
}

void GeneticAlgorithm::ChangeInputs(std::vector<float> in)
{
	//if (instanceCount > 0)
	//{
	//	for (int i = 0; i < instanceCount; i++)
	//	{
	//		ins
	//	}
	//}
}