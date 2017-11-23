#include "GameObject.h"



GameObject::GameObject(std::string name = "GameObject",
					   Transform _transform,
					   Model* _model,
					   Mesh* _mesh,
					   Shader* _shader,
					   Texture* _texture)
	:transform(_transform), model(_model), mesh(_mesh), shader(_shader), texture(_texture)
{

}

GameObject::~GameObject()
{
	if (model != nullptr)
	{
		delete model;
		model = nullptr;

	}
	if (mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}
}

void GameObject::Update()
{
	

}

void GameObject::Draw()
{
	if (shader != nullptr)
	{		
		shader->Bind();
		shader->Update(transform);
	}
	if (texture != nullptr)
	{
		texture->Bind(0);
	}
	if (mesh != nullptr)
	{
		mesh->Draw();
	}
	if (model != nullptr)
	{
		model->Draw();
	}

}
