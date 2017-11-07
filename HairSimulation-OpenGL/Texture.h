#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture();
	Texture(std::string filePath);
	~Texture();

	//static GLint TextureFromFile(const char *path, std::string directory);

	void Bind(unsigned int unit);

	GLuint m_texture;
	std::string type;
	std::string path;
protected:
private:
	//Texture(const Texture& other);
	//void operator=(const Texture& other);
};

