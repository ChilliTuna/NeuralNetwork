#include <iostream>
#include <string>

#include "Test.h"
#include "Node.h"
#include "Tools.h"

float TempTest(std::vector<float> vals)
{
	float sum = 0;
	for (int i = 0; i < vals.size(); i++)
	{
		sum += vals[i];
	}
	return sum;
}

int main()
{
	Node node(TempTest);
	float test[] = { 1.0f, 4.0f, 3.0f, 5.0f };
	node.SetInputs(ArrayToVector(test, 4));
	std::cout << std::to_string(node.CallActivationFunction());

	return 0;
}