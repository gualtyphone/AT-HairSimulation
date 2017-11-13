#include "Model.h"



Model::Model(std::string filePath)
{
	loadModel(filePath);
}

Model::~Model()
{
	//TODO: clean up
}

void Model::Draw()
{

	// TODO: if there are textures in the model bind them to the right mesh
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		if (texturesLoaded.size() > 0)
		{
			texturesLoaded[i]->Bind(0);
		}
		meshes[i]->Draw();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error: Assimp: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

		meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indicies;
	std::vector<Texture*> textures;
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		Vector3 vector(mesh->mVertices[i].x,
					   mesh->mVertices[i].y,
					   mesh->mVertices[i].z);
		vertex.SetPos(vector);

		if (mesh->HasNormals())
		{

			Vector3 normal(mesh->mNormals[i].x,
						   mesh->mNormals[i].y,
						   mesh->mNormals[i].z);
			vertex.SetNormal(normal);
		}
		else
		{
			//vertex.Normal = Vector3(0.0, 0.0, 0.0);
		}
		if (mesh->mTextureCoords[0])
		{
			Vector2 texCoords(mesh->mTextureCoords[0][i].x,
							  mesh->mTextureCoords[0][i].y);
			vertex.SetTexCoord(texCoords);
		}
		else
		{
			vertex.SetTexCoord(Vector2(0.0, 0.0));
		}
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indicies.push_back(face.mIndices[j]);
		}
	}
	Mesh* newMesh = new Mesh(vertices, indicies);
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture*> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());
		if (diffuseMap.size() > 0)
			newMesh->SetTexture(texturesLoaded[texturesLoaded.size()-1]);

		std::vector<Texture*> specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMap.begin(), specularMap.end());
	}

	return newMesh;
}

std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture*> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;
		for (GLuint j = 0; j < texturesLoaded.size(); j++)
		{
			if (*texturesLoaded[j]->GetPath() == str.C_Str())
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
			}
		}

		if (!skip)
		{
			Texture* texture = new Texture(directory + '/' + std::string(str.C_Str()), typeName);
			//texture.type = typeName;
			//texture.path = str.C_Str();

			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}
