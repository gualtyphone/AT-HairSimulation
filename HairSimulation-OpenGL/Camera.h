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
		right = Vector3(1, 0, 0);
	}
	~Camera();

	void Update();

	void Move(Vector3 direction)
	{
		position = position + direction;
	}

	inline Matrix4 GetVewProjection() const
	{
		//return *GMath::perspective(1.4, 1.1, 0.1f, 100000.0f);
		return (*(persp) * lookAt(position, forward, up));
	}

protected:
private:
	Vector3 position;
	Matrix4* persp;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	Vector3 rotation;

	bool mouseFocus = false;
};

