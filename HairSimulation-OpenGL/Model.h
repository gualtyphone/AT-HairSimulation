#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Display.h"
#include "Transform.h"
#include "GMath.h"
#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model(std::string filePath);
	~Model();

	virtual void Draw();

protected:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh (aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string directory;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> texturesLoaded;

private:
};

