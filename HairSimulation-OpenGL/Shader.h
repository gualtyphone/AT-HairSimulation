#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Display.h"

class Shader
{
public:
	Shader(std::string& fileName);
	virtual ~Shader();

	void Bind();
//protected:
//private:
	enum
	{
		VERTEX_SHADER = 0,
		FRAGMENT_SHADER = 1,

		NUM_SHADERS
	};
	/*Shader(const Shader& other);
	void operator=(const Shader& other);
*/
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

