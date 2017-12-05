#include "Camera.h"
#include "Input.h"
#include <string>
#include <crtdbg.h>

void Camera::Update()
{
	if (Input::GetKey(KeyCode::W))
	{
		position = position + forward / 10;
	}
	if (Input::GetKey(KeyCode::S))
	{
		position = position - forward / 10;
	}
	if (Input::GetKey(KeyCode::A))
	{
		position = position - right / 10;
	}
	if (Input::GetKey(KeyCode::D))
	{
		position = position + right / 10;
	}
	if (Input::GetKey(KeyCode::LeftShift))
	{
		position = position - up / 10;
	}
	if (Input::GetKey(KeyCode::Space))
	{
		position = position + (up/10);
	}
	if (Input::GetKey(KeyCode::Mouse1))
	{
		if (Input::MouseMoved())
		{
			Vector2 mousePos = Input::GetMousePosition();
			Vector2 prevMousePos = Input::GetPreviousMousePosition();

			Vector2 change = mousePos - prevMousePos;

			rotation = rotation + Vector3(change.y * 0.001f, change.x * 0.001f, 0.0f);

			Matrix4 matX = rotateAroundXAxis(rotation.GetX());
			Matrix4 matY = rotateAroundYAxis(rotation.GetY());
			Matrix4 matZ = rotateAroundZAxis(rotation.GetZ());

			Matrix4 rotMat =matX * matY *  matZ;

			forward = Vector3(rotMat.Get(2), rotMat.Get(6), rotMat.Get(10));
			up = Vector3(rotMat.Get(1), rotMat.Get(5), rotMat.Get(9));

			forward.normalize();
			up.normalize();
			right = Vector3::cross(forward, up);
			right.normalize();

			//up = Vector3() - up;
			//std::string error =  "RotX:" + std::to_string(rotation.GetX()) + "RotY:" + std::to_string(rotation.GetY()) + "\n";
			//_RPT0(_CRT_ERROR, error.c_str());
		}
	}
}
