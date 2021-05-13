#include <iostream>
#include <string>

#include "Test.h"
#include "NeuralNetwork.h"

float TempTest(float in)
{
	return in * 10;
}

int main()
{
	srand(time(0));
	//Neuron mainNeuron(TempTest);
	//Neuron testNeuron;
	//testNeuron.output = 5;
	//mainNeuron.AddInput(&testNeuron);
	//mainNeuron.Calculate();
	//std::cout << std::to_string(mainNeuron.output) << std::endl;

	std::vector<std::vector<std::vector<float>>> weights =
	{
		{{}},
		{{-1}, {1}}
	};

	TestDLL();

	NeuralNetwork* brain = new NeuralNetwork({ 2, 1 });

	float myPos = 5;
	float targetPos = 3;

	std::vector<float*> testInputs = { &myPos, &targetPos };
	brain->SetInputs(testInputs);
	brain->SetWeights(weights);
	//brain[1][0]->ChangeWeight(brain[0][0], -1);


	NeuralNetwork brain2electricboogaloo = *brain;

	weights[1][0][0] = -2.0f;
	brain->SetWeights(weights);

	brain->Update();
	brain2electricboogaloo.Update();

	std::cout << "I need to move to the right by " << std::to_string(brain->GetOutputs()[0]) << std::endl;
	std::cout << "I need to move to the right by " << std::to_string(brain2electricboogaloo.GetOutputs()[0]) << std::endl;

	return 0;
}