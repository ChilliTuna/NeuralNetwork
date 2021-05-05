#pragma once
#include "DLLHandler.h"

#include <vector>

typedef float (*ActivationFunction)(float[]);

class Node
{
	ActivationFunction actFunc = nullptr;
public:

	std::vector<float> inputs;
	float output;

	Node() {}
	Node(ActivationFunction function)
	{
		SetActivationFunction(function);
	}

	API void SetActivationFunction(ActivationFunction function);

	API float CallActivationFunction();
};