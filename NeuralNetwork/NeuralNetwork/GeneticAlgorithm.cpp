#include "GeneticAlgorithm.h"
#include <random>

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
	for (int i = 0; i < instanceCount; i++)
	{
		instances[i].Saturate();
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
	std::mt19937 engine(1729);
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

	std::vector<NeuralNetwork> sortedNetworks;
	std::vector<float> networkPerformances; 
	if (instanceCount > 0)
	{
		sortedNetworks.push_back(instances[0]);
		networkPerformances.push_back(fitnessFunc(checkVals[0]));
	}
	float fitness;
	for (int i = 0; i < instanceCount; i++)
	{
		fitness = fitnessFunc(checkVals[i]);
		for (int j = 0; j < sortedNetworks.size(); j++)
		{
			if (fitness < networkPerformances[j])
			{
				sortedNetworks.insert(sortedNetworks.begin() + j, instances[i]);
				networkPerformances.insert(networkPerformances.begin() + j, fitness);
				break;
			}
		}
	}
	nextGenProgenitors = sortedNetworks;
}

void GeneticAlgorithm::Update()
{
	for (int i = 0; i < instanceCount; i++)
	{
		instances[i].Update();
	}
}