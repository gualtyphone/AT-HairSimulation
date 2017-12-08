#pragma once
#include "GMath.h"

using namespace GMath;

class Lighting
{
public:
	Lighting();
	~Lighting();

	static inline Vector3* GetLight()
	{
		return &lightDirection;
	}

	static inline void SetLight(Vector3& newDir)
	{
		lightDirection = newDir;
	}

protected:
private:
	static Vector3 lightDirection;
};

