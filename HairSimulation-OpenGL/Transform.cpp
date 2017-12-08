#include "Transform.h"

Transform::Transform(const Transform & other)
{
	mat = other.mat;
	Position = other.Position;
	Rotation = other.Rotation;
	Scale = other.Scale;
	Update();


}

Transform::~Transform()
{}
