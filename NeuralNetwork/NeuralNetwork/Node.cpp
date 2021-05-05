#include "Node.h"

void Node::SetActivationFunction(ActivationFunction function)
{
	actFunc = function;
}

float Node::CallActivationFunction()
{
	return actFunc(inputs);
}