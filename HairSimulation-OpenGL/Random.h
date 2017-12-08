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

	inline static Vector3 Vec3(float min = 0, float max = 1)
	{
		return Vector3(Range(min, max), Range(min, max), Range(min, max));
	}
};

