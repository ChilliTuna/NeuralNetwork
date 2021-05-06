#include "Neuron.h"

void Neuron::SetInput(std::vector<Neuron*> inputs, std::vector<float> weights)
{
	this->inputs = inputs;
	this->weights = weights;
	if (weights.size() < inputs.size())
	{
		for (int i = weights.size(); i <= inputs.size(); i++)
		{
			weights.push_back(1);
		}
	}
}

void Neuron::AddInput(Neuron* input, float weight)
{
	inputs.push_back(input);
	weights.push_back(weight);
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
	float sum = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		sum += (inputs[i]->output * weights[i]);
	}
	return sum + bias;
}

float Neuron::CallActivationFunction()
{
	return actFunc(output);
}