#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
#include <crtdbg.h>

Texture::Texture()
{}

Texture::Texture(std::string filePath, std::string typeName)
{
	int width, height, numComponents;
	path = filePath;
	type = typeName;
	unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture Loading Failed for texture: " << filePath << std::endl;

	glGenTextures(1, &m_texture);
	auto err1 = glGetError();
	_RPT0(_CRT_ERROR, "Generating Texture\n" );
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
				 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	auto err = glGetError();
	stbi_image_free(imageData);
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

