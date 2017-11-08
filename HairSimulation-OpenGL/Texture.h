#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture();
	Texture(std::string filePath, std::string typeName);
	~Texture();

	void Bind(unsigned int unit);

	inline std::string* GetPath() { return &path; }
	inline std::string* GetType() { return &type; }

protected:
private:
	//Texture(const Texture& other);
	//void operator=(const Texture& other);

	GLuint m_texture;
	std::string type;
	std::string path;

};

