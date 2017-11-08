#pragma once
#include <math.h>
namespace GMath
{
	class Matrix4;
	class Vector3;
	class Vector2;
	class Quaternion;

	class Vector3
	{
	public:
		Vector3();
		Vector3(float _x, float _y, float _z);
		~Vector3();

		inline float const GetX() const
		{
			return x;
		}
		inline float const GetY() const
		{
			return y;
		}
		inline float const GetZ() const
		{
			return z;
		}

	protected:
	private:
		float x;
		float y;
		float z;
	};

	class Vector2
	{
	public:
		Vector2();
		Vector2(float _x, float _y);
		~Vector2();

	protected:
	private:
		float x;
		float y;
	};

	class Quaternion
	{
	public:
		Quaternion();
		~Quaternion();

		inline float const GetX() const
		{
			return x;
		}
		inline float const GetY() const
		{
			return y;
		}
		inline float const GetZ() const
		{
			return z;
		}
		inline float const GetW() const
		{
			return w;
		}

	private:
		float x;
		float y;
		float z;
		float w;
	};

	Matrix4 translate(Vector3);
	Matrix4 rotateAroundXAxis(float);
	Matrix4 rotateAroundYAxis(float);
	Matrix4 rotateAroundZAxis(float);
	Matrix4 rotate(Quaternion);
	Matrix4 scale(Vector3);

	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(float _11, float  _12, float  _13, float  _14,
				float _21, float  _22, float  _23, float  _24,
				float _31, float  _32, float  _33, float  _34,
				float _41, float  _42, float  _43, float  _44);

		~Matrix4();

		friend Matrix4 operator*(Matrix4&, Matrix4&);

		inline float* Get() const
		{
			return m;
		}

	private:
		float* m;
	};

}