#pragma once

#include <vector>
#include "VectorMath.h"
#include "Texture.h"
#include "Shader.h"
#include <GL\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <sstream>

class Vertex
{
public:
	Vertex()
	{
	}

	Vertex(const Vector3& _Position)
	{
		this->Position = _Position;
	}

	Vertex(const Vector3& _Position, const Vector2& _TexCoords)
	{
		this->Position = _Position;
		this->TexCoords = _TexCoords;
	}

	//Vertex(const Vector3& _Position, const Vector2& _TexCoords/*, const Vector3& _Normal*/)
	//{
	//	this->Position = _Position;
	//	this->TexCoords = _TexCoords;
	//	//this->Normal = _Normal;
	//}
//private:
	Vector3 Position;
	Vector2 TexCoords;
	//Vector3 Normal;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	void Draw();

protected:
private:
	Mesh(const Mesh& otehr);
	void operator=(const Mesh& otehr);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	std::vector<Vector3> positions;
	std::vector<Vector2> texCoords;
	std::vector<GLuint> indicies;

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

};

