#pragma once
#include "DLLHandler.h"

#include <vector>

typedef float (*ActivationFunction)(float);

class Neuron
{
	ActivationFunction actFunc = nullptr;

	std::vector<Neuron*> inputs;
	std::vector<float> weights;

	float Summate();
	float CallActivationFunction();

public:
	float bias = 0;

	float output = 0;

	Neuron() {}
	Neuron(ActivationFunction function)
	{
		SetActivationFunction(function);
	}
	
	API void SetInput(std::vector<Neuron*> inputs, std::vector<float> weights);

	API void AddInput(Neuron* input, float weight = 1);
	
	API void SetActivationFunction(ActivationFunction function);

	API void Calculate();
};