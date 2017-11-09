#pragma once
#include "GMath.h"
using namespace GMath;

class Camera
{
public:
	Camera(Vector3 pos, float fov, float aspect, float zNear, float zFar)
	{
		persp = new Matrix4();
		persp = GMath::perspective(fov, aspect, zNear, zFar);
		position = pos;
		forward = Vector3(0, 0, 1);
		up = Vector3(0, 1, 0);
	}
	~Camera();

	inline Matrix4 GetVewProjection() const
	{
		Matrix4 view = lookAt(position, position + forward, up);
		return *persp * view;
	}

protected:
private:
	Vector3 position;
	Matrix4* persp;
	Vector3 forward;
	Vector3 up;

};

