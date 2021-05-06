#pragma once
#include <vector>

std::vector<float> ArrayToVector(float array[], int length)
{
	return std::vector<float>(array, array + length);
}