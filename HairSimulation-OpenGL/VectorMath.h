#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

	float x;
	float y;
	float z;
protected:
private:
}; 

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

	float x;
	float y;
protected:
private:
};