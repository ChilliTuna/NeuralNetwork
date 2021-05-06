#pragma once

#include "Neuron.h"

class NeuralNetwork
{
	typedef std::vector<Neuron*> column;
	std::vector<column> network;

	API void Update();
};