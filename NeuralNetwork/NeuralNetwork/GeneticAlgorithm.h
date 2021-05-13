#pragma once
#include <vector>
#include "DLLHandler.h"
#include "NeuralNetwork.h"

class GeneticAlgorithm
{
public:
	NeuralNetwork* originalNetwork;
	std::vector<NeuralNetwork> instances;

	std::vector<NeuralNetwork> nextGenProgenitors;

	int generationCount = 0;

	float instanceCount;
	float breedersCount;

	float generationalVariance = 1;

	API void CreateFirstGen();
	API void CreateNewGen();
	API void RandomiseWeights(NeuralNetwork* instancesToModify, float maxNegDif, float maxPosDif);
	API void RandomiseAllWeights(float maxNegDif, float maxPosDif);
	API void Update();
};
