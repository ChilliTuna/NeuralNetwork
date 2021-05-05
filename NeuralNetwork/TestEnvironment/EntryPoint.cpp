#include "Test.h"
#include "Node.h"

float TempTest(float vals[])
{
	float sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += vals[i];
	}
	return sum;
}

int main()
{
	Node node(TempTest);

	node.inputs = { 1, 4, 3, 2 };
	node.CallActivationFunction();

	return 0;
}