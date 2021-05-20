#include "NeuralNetwork.h"
#include <fstream>

NeuralNetwork::NeuralNetwork(std::vector<short> columnSizes, bool saturate, ActivationFunction defaultFunc)
{
	GenerateNetwork(columnSizes, saturate);
	this->defaultFunc = defaultFunc;
}

void NeuralNetwork::Update()
{
	for (int i = 0; i < network.size(); i++)
	{
		for (int j = 0; j < network[i].size(); j++)
		{
			network[i][j].Calculate();
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
	std::vector<Neuron*> prevCol;
	if (network.size() > 0)
	{
		for (int i = 0; i < network.back().size(); i++)
		{
			prevCol.push_back(&(network.back()[i]));
		}
	}
	Column temp;
	for (int j = 0; j < size; j++)
	{
		if (defaultFunc != nullptr)
		{
			temp.push_back(Neuron(defaultFunc));
		}
		else
		{
			temp.push_back(Neuron());
		}
		if (saturate)
		{
			if (network.size() > 0)
			{
				temp[j].SetInput(prevCol);
			}
		}
	}
	network.push_back(temp);
}

void NeuralNetwork::AddNeuron(Neuron* newNeuron, short column, bool saturate)
{
	network[column].push_back(*newNeuron);
	if (saturate)
	{
		if (column > 0)
		{
			std::vector<Neuron*> prevCol;
			for (int i = 0; i < network[column - 1].size(); i++)
			{
				prevCol.push_back(&(network[column - 1][i]));
			}
			newNeuron->SetInput(prevCol);
		}
	}
}

void NeuralNetwork::SetInputs(std::vector<float> inputs)
{
	if (network.size() > 0)
	{
		for (int i = 0; i < network[0].size(); i++)
		{
			network[0][i].SetInput(inputs[i]);
		}
	}
}

void NeuralNetwork::SetInputs(std::vector<float*> inputs)
{
	if (network.size() > 0)
	{
		for (int i = 0; i < network[0].size(); i++)
		{
			network[0][i].SetInput(inputs[i]);
		}
	}
}

void NeuralNetwork::ConnectNeurons(short from, short to, short fromColumn)
{
	if (network.size() > fromColumn)
	{
		if (network[fromColumn].size() > from&& network[fromColumn + 1].size() > to)
		{
			ConnectNeurons(&network[fromColumn + 1][from], &network[fromColumn][to]);
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

void NeuralNetwork::Saturate()
{
	for (int i = 1; i < network.size(); i++)
	{
		std::vector<Neuron*> prevCol;
		for (int j = 0; j < network[i - 1].size(); j++)
		{
			prevCol.push_back(&network[i - 1][j]);
		}
		for (int j = 0; j < network[i].size(); j++)
		{
			network[i][j].SetInput(prevCol, network[i][j].GetWeights());
		}
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
			if (&network[i][j] == checkNeuron)
			{
				return true;
			}
		}
	}
	return false;
}

bool NeuralNetwork::ContainsIndex(short index, short column)
{
	if (network.size() > column&& network[column].size() > index)
	{
		return true;
	}
	return false;
}

//UNSAFE!!! Ensure neuron exists BEFORE calling
Neuron* NeuralNetwork::GetNeuron(short index, short column)
{
	return &network[column][index];
}

void NeuralNetwork::Save(std::string fileName)
{
	std::fstream stream;
	stream.open(fileName.c_str(), std::ios::out | std::ios::binary);
	stream.write(reinterpret_cast<char*>(this), sizeof(*this));
	stream.close();
}

std::vector<float> NeuralNetwork::GetOutputs()
{
	if (network.size() > 0)
	{
		if (network.back().size() > 0)
		{
			std::vector<float> retVec;
			for (int i = 0; i < network.back().size(); i++)
			{
				retVec.push_back(network.back()[i].output);
			}
			return retVec;
		}
	}
	return { 0 };
}

std::vector<Neuron>* NeuralNetwork::operator[](int index)
{
	return &network[index];
}