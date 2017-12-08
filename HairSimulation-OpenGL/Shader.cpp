#include "Shader.h"
#include <crtdbg.h>

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(std::string& fileName)
{
	shaderName = fileName;
	m_program = glCreateProgram();
	m_shaders[VERTEX_SHADER] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[FRAGMENT_SHADER] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[LIGHTDIR_U] = glGetUniformLocation(m_program, "lightDirection");

}

Shader::Shader(std::string & fileName, Camera * _camera)
	:Shader(fileName)
{
	camera = _camera;
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform & transform, const Camera& cam)
{
	glUseProgram(m_program);
	Matrix4 m = cam.GetVewProjection() * transform.Get();
	glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE, &(m.Get()[0]));
	
}

void Shader::Update(const Transform & transform, const Camera & cam, const  Vector3& lightDir)
{
	glUseProgram(m_program);
	Matrix4 m = camera->GetVewProjection() * transform.Get();
	glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE, &(m.Get()[0]));
	glUniform3f(m_uniforms[1], lightDir.GetX(), lightDir.GetY(), lightDir.GetZ());
}

void Shader::Update(const Transform & transform)
{
	Update(transform, *camera);
}

void Shader::Update(const Transform & transform, const Vector3& lightDir)
{
	Update(transform, *camera, lightDir);
}

void Shader::Update(const Matrix4 & transform)
{
	glUseProgram(m_program);
	Matrix4 m = camera->GetVewProjection() * transform;
	glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE, &(m.Get()[0]));
}
void Shader::Update(const Matrix4 & transform, const Vector3& lightDir)
{
	glUseProgram(m_program);
	Matrix4 m = camera->GetVewProjection() * transform;
	glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE, &(m.Get()[0]));
	glUniform3f(m_uniforms[1], lightDir.GetX(), lightDir.GetY(), lightDir.GetZ());

}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		_RPT0(_CRT_ERROR, "Error: Shader creation failed\n"); 

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, true, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		_RPT0(_CRT_ERROR, "Unable to load shader: " + fileName);
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 1;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		_RPT0(_CRT_ERROR, (errorMessage + ": '" + error + "'\n").c_str());
		
	}
}