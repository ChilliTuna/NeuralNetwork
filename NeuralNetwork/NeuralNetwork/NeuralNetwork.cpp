#include "NeuralNetwork.h"

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
