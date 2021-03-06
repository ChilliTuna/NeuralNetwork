#include "Neuron.h"

void Neuron::SetInput(std::vector<Neuron*> inputs, std::vector<float> weights)
{
	this->inputs = inputs;
	this->weights = weights;
	if (weights.size() < inputs.size())
	{
		for (int i = weights.size(); i < inputs.size(); i++)
		{
			this->weights.push_back(1);
		}
	}
}

void Neuron::SetInput(float input)
{
	staticInput = input;
	dynamicInput = &staticInput;
	firstColumn = true;
}

void Neuron::SetInput(float* input)
{
	dynamicInput = input;
	firstColumn = true;
}

void Neuron::AddInput(Neuron* input, float weight)
{
	inputs.push_back(input);
	weights.push_back(weight);
}

short Neuron::GetWeightsCount()
{
	return weights.size();
}

API float Neuron::GetWeight(short index)
{
	if (index < GetWeightsCount())
	{
		return weights[index];
	}
	return NULL;
}

API std::vector<float> Neuron::GetWeights()
{
	return weights;
}

void Neuron::ChangeWeight(int index, float newVal)
{
	if (index < weights.size())
	{
		weights[index] = newVal;
	}
}

void Neuron::ChangeWeight(Neuron* synapse, float newVal)
{
	for (int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] == synapse)
		{
			weights[i] = newVal;
		}
	}
}

void Neuron::SetActivationFunction(ActivationFunction function)
{
	actFunc = function;
}

void Neuron::Calculate()
{
	output = Summate();
	output = CallActivationFunction();
}

float Neuron::Summate()
{
	if (firstColumn)
	{
		return *dynamicInput;
	}
	float sum = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		sum += (inputs[i]->output * weights[i]);
	}
	return sum + bias;
}

float Neuron::CallActivationFunction()
{
	if (actFunc != nullptr)
	{
		return actFunc(output);
	}
	return output;
}