#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	m_drawCount = indices.size();

	//create vertex array
	glGenVertexArrays(1, &m_vertexArrayObject);
	//load vertex array
	glBindVertexArray(m_vertexArrayObject);

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		positions.push_back(vertices[i].Position);
		texCoords.push_back(vertices[i].TexCoords);
	}

	for (int i = 0; i < indices.size(); i++)
	{
		indicies.push_back(indices[i]);
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);

	//clear loaded vertex array
	glBindVertexArray(0);

}



Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* _indices, unsigned int numIndices)
{
	m_drawCount = numIndices;

	//create vertex array
	glGenVertexArrays(1, &m_vertexArrayObject);
	//load vertex array
	glBindVertexArray(m_vertexArrayObject);
	
	/*std::vector<Vector3> positions;
	std::vector<Vector2> texCoords;*/

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].Position);
		texCoords.push_back(vertices[i].TexCoords);
	}
	//std::vector<unsigned int> indices;
	for (int i = 0; i < numIndices; i++)
	{
		indicies.push_back(_indices[i]);
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);

	//clear loaded vertex array
	glBindVertexArray(0); 

}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
}
