#include "NeuralNetwork.h"

NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < network.size(); i++)
	{
		for (int j = 0; j < network[i].size(); j++)
		{
			delete network[i][j];
		}
	}
}

void NeuralNetwork::Update()
{
	for (int i = 0; i < network.size(); i++)
	{
		for (int j = 0; j < network[i].size(); j++)
		{
			network[i][j]->Calculate();
		}
	}
}

void NeuralNetwork::GenerateNetwork(std::vector<float> columnSizes, bool saturate)
{
	for (int i = 0; i < columnSizes.size(); i++)
	{
		AddColumn(columnSizes[i], saturate);
	}
}

void NeuralNetwork::AddColumn(float size, bool saturate)
{
	Column temp;
	for (int j = 0; j < size; j++)
	{
		if (defaultFunc != nullptr)
		{
			temp.push_back(new Neuron(defaultFunc));
		}
		else
		{
			temp.push_back(new Neuron());
		}
		if (saturate)
		{
			if (network.size() > 0)
			{
				temp[j]->SetInput(network.back());
			}
		}
	}
	network.push_back(temp);
}

void NeuralNetwork::AddNeuron(Neuron* newNeuron, short column, bool saturate)
{
	network[column].push_back(newNeuron);
	if (saturate)
	{
		if (column > 0)
		{
			newNeuron->SetInput(network[column - 1]);
		}
	}
}

void NeuralNetwork::SetInputs(std::vector<float> inputs)
{
	if (network.size() > 0)
	{
		for (int i = 0; i < network[0].size(); i++)
		{
			network[0][i]->SetInput(inputs[i]);
		}
	}
}

void NeuralNetwork::SetInputs(std::vector<float*> inputs)
{
	if (network.size() > 0)
	{
		for (int i = 0; i < network[0].size(); i++)
		{
			network[0][i]->SetInput(inputs[i]);
		}
	}
}

void NeuralNetwork::ConnectNeurons(int from, int to, int fromColumn)
{
	if (fromColumn > network.size())
	{
		if (network[fromColumn].size() > from && network[fromColumn + 1].size() > to)
		{
			ConnectNeurons(network[fromColumn + 1][from], network[fromColumn][to]);
		}
	}
}

void NeuralNetwork::ConnectNeurons(Neuron* from, Neuron* to)
{
	if (ContainsNeuron(from) && ContainsNeuron(to))
	{
		to->AddInput(from);
	}
}

bool NeuralNetwork::ContainsNeuron(Neuron* checkNeuron)
{
	for (int i = 0; i < network.size(); i++)
	{
		for (int j = 0; j < network[i].size(); j++)
		{
			if (network[i][j] == checkNeuron)
			{
				return true;
			}
		}
	}
	return false;
}

std::vector<float> NeuralNetwork::GetOutputs()
{
	std::vector<float> retVec;
	for (int i = 0; i < network.back().size(); i++)
	{
		retVec.push_back(network.back()[i]->output);
	}
	return retVec;
}