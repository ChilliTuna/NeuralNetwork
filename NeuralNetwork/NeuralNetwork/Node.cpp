#include "Node.h"

void Node::SetInputs(std::vector<float> in)
{
	inputs = in;
}

void Node::SetActivationFunction(ActivationFunction function)
{
	actFunc = function;
}

float Node::CallActivationFunction()
{
	return actFunc(inputs);
}