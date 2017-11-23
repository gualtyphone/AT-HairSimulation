#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Display.h"
#include "GMath.h"
#include "Transform.h"
#include "Camera.h"


class Shader
{
public:
	Shader(std::string& fileName);
	Shader(std::string& fileName, Camera* _camera);
	virtual ~Shader();

	void Bind();
	void Update(const Transform& transform, const Camera& cam);
	void Update(const Transform& transform);

protected:
private:
	//Shader(const Shader& other);
	//void operator=(const Shader& other);
	std::string shaderName;
	Camera* camera;

	enum
	{
		VERTEX_SHADER = 0,
		FRAGMENT_SHADER = 1,

		NUM_SHADERS
	};

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORM
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORM];

};

