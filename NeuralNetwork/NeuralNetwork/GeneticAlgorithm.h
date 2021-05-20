#pragma once
#include <vector>
#include "DLLHandler.h"
#include "NeuralNetwork.h"
#include <random>

class GeneticAlgorithm
{
public:
	NeuralNetwork* originalNetwork;
	std::vector<NeuralNetwork> instances;

	std::vector<NeuralNetwork> nextGenProgenitors;

	//Higher values are considered better
	float(*fitnessFunc)(std::vector<float>);

	int generationCount = 0;

	int instanceCount = 10;
	int breedersCount = 2;

	float generationalVariance = 0.1f;

	NeuralNetwork best;

	std::mt19937 engine;

	API GeneticAlgorithm();
	API GeneticAlgorithm(const GeneticAlgorithm& other) = delete;
	API GeneticAlgorithm& operator=(const GeneticAlgorithm& other) = delete;
	API void CreateFirstGen();
	API void CreateNewGen();
	API void RandomiseWeights(NeuralNetwork* instancesToModify, float maxNegDif, float maxPosDif);
	API void RandomiseAllWeights(float maxNegDif, float maxPosDif);
	API void CompletelyRandomiseWeights(float min, float max);
	API void RunGenerationalGuantlet(std::vector<std::vector<float>> checkVals);
	API void RunFitnessFunc(std::vector<std::vector<float>> checkVals);
	API void Update();
};
