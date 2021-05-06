#pragma once
#include "DLLHandler.h"

#include <vector>

typedef float (*ActivationFunction)(std::vector<float>);

class Node
{
	ActivationFunction actFunc = nullptr;

	std::vector<float> inputs;

public:

	float output;

	Node() {}
	Node(ActivationFunction function)
	{
		SetActivationFunction(function);
	}

	API void SetInputs(std::vector<float> in);
	
	API void SetActivationFunction(ActivationFunction function);

	API float CallActivationFunction();
};