#pragma once

#include "Neuron.h"

class NeuralNetwork
{
	std::vector<float> inputs;

public:
	typedef std::vector<Neuron*> Column;
	std::vector<Column> network;

	ActivationFunction defaultFunc = nullptr;

	NeuralNetwork() {};
	API ~NeuralNetwork();

	API void Update();

	API void GenerateNetwork(std::vector<float> columnSizes, bool saturate = true);
	API void AddColumn(float size, bool saturate = true);
	API void AddNeuron(Neuron* newNeuron, short column, bool saturate = false);
	API void SetInputs(std::vector<float> inputs);
	API std::vector<float> GetOutputs();
};