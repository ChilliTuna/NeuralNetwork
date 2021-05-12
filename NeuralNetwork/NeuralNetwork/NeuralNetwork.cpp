#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<short> columnSizes, bool saturate)
{
	GenerateNetwork(columnSizes, saturate);
}

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

void NeuralNetwork::GenerateNetwork(std::vector<short> columnSizes, bool saturate)
{
	for (int i = 0; i < columnSizes.size(); i++)
	{
		AddColumn(columnSizes[i], saturate);
	}
}

void NeuralNetwork::AddColumn(short size, bool saturate)
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

void NeuralNetwork::ConnectNeurons(short from, short to, short fromColumn)
{
	if (network.size() > fromColumn)
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

void NeuralNetwork::ChangeWeight(short from, short to, short fromColumn, float newVal)
{
	if (ContainsIndex(from, fromColumn) && ContainsIndex(to, fromColumn + 1))
	{
		GetNeuron(to, fromColumn + 1)->ChangeWeight(GetNeuron(from, fromColumn), newVal);
	}
}

void NeuralNetwork::ChangeWeight(Neuron* neuron, short synapseIndex, float newVal)
{
	neuron->ChangeWeight(synapseIndex, newVal);
}

void NeuralNetwork::ChangeWeight(Neuron* fromNeuron, Neuron* toNeuron, float newVal)
{
	toNeuron->ChangeWeight(fromNeuron, newVal);
}

void NeuralNetwork::SetWeights(std::vector<std::vector<std::vector<float>>> weights)
{
	for (int i = 0; i < weights.size(); i++)
	{
		for (int j = 0; j < weights[i].size(); j++)
		{
			for (int k = 0; k < weights[i][j].size(); k++)
			{
				if (ContainsIndex(j, i))
				{
					ChangeWeight(GetNeuron(j, i), k, weights[i][j][k]);
				}
			}
		}
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

bool NeuralNetwork::ContainsIndex(short index, short column)
{
	if (network.size() > column && network[column].size() > index)
	{
		return true;
	}
	return false;
}

//UNSAFE!!! Ensure neuron exists BEFORE calling
Neuron* NeuralNetwork::GetNeuron(short index, short column)
{
	return network[column][index];
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

std::vector<Neuron*> NeuralNetwork::operator[](int index)
{
	return network[index];
}