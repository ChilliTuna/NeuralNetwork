#pragma once

#include "Neuron.h"
#include <string>

class NeuralNetwork
{

public:
	typedef std::vector<Neuron> Column;
	std::vector<Column> network;

	float fitness = 0;

	ActivationFunction defaultFunc = nullptr;

	API NeuralNetwork() {};
	API NeuralNetwork(std::vector<short> columnSizes, bool saturate = true, ActivationFunction defaultFunc = nullptr);

	API void Update();

	API void GenerateNetwork(std::vector<short> columnSizes, bool saturate = true);
	API void AddColumn(short size, bool saturate = true);
	API void AddNeuron(Neuron* newNeuron, short column, bool saturate = false);
	API void SetInputs(std::vector<float> inputs);
	API void SetInputs(std::vector<float*> inputs);
	API void ConnectNeurons(short from, short to, short fromColumn);
	API void ConnectNeurons(Neuron* from, Neuron* to);
	API void Saturate();
	API void ChangeWeight(short from, short to, short fromColumn, float newVal);
	API void ChangeWeight(Neuron* neuron, short neuronIndex, float newVal);
	API void ChangeWeight(Neuron* fromNeuron, Neuron* toNeuron, float newVal);
	API void SetWeights(std::vector<std::vector<std::vector<float>>> weights);
	API bool ContainsNeuron(Neuron* checkNeuron);
	API bool ContainsIndex(short index, short column);
	API Neuron* GetNeuron(short index, short column);
	API void Save(std::string fileName);
	API NeuralNetwork Load(std::string fileName);
	API std::vector<float> GetOutputs();
	API std::vector<Neuron>* operator[](int index);

};