#pragma once
#include <random>

class Random
{
public:
	Random();
	~Random();

	inline static float Range(float min, float max)
	{
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}
};

