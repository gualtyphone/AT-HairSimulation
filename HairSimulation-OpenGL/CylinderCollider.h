#pragma once
#include <GL\glew.h>
#include <math.h>
#include "Transform.h"

#define PI 3.1415927
class CylinderCollider
{
public:
	CylinderCollider(Transform _transform = Transform(), float _radius = 1.0f, float _height = 2.0f);
	~CylinderCollider();

	Transform transform;
	float radius = 1.0f;
	float height = 2.0f;

	void Draw();
};

