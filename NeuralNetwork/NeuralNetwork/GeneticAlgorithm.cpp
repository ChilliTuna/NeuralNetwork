#include "GeneticAlgorithm.h"
#include <random>

void GeneticAlgorithm::CreateFirstGen()
{
	generationCount = 1;
	for (int i = 0; i < instanceCount; i++)
	{
		instances.push_back(*originalNetwork);
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
	RandomiseAllWeights(generationalVariance / 2 - generationalVariance, generationalVariance / 2 + generationalVariance);
	generationCount++;
}

void GeneticAlgorithm::RandomiseWeights(NeuralNetwork* instanceToModify, float negGeneticDif, float posGeneticDif)
{
	std::mt19937 engine(1729);
	std::uniform_real_distribution<float> distribution(negGeneticDif, posGeneticDif);
	for (int i = 0; i < instanceToModify->network.size(); i++)
	{
		for (int j = 0; j < instanceToModify->network[i].size(); j++)
		{
			for (int k = 0; k < instanceToModify->network[i][j]->GetWeightsCount(); k++)
			{
				instanceToModify->network[i][j]->ChangeWeight(k, instanceToModify->network[i][j]->GetWeight(k) + distribution(engine));
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

void GeneticAlgorithm::Update()
{
	for (int i = 0; i < instanceCount; i++)
	{
		instances[i].Update();
	}
}
