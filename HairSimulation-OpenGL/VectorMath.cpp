#include "VectorMath.h"

Vector3::Vector3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3::Vector3(float _x = 0.0, float _y = 0.0, float _z = 0.0)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::~Vector3()
{

}


Vector2::Vector2()
{
	x = 0.0;
	y = 0.0;
}

Vector2::Vector2(float _x = 0.0, float _y = 0.0)
{
	x = _x;
	y = _y;
}

Vector2::~Vector2()
{

}
