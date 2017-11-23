#pragma once
#include "Transform.h"
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject(std::string name, Transform = Transform(),
			   Model* = nullptr,
			   Mesh* = nullptr,
			   Shader* = nullptr,
			   Texture* = nullptr);
	~GameObject();

	virtual void Update();
	virtual void Draw();

	inline Transform* GetTransform() { return &transform; }
protected:
private:
	std::string name = "GameObject";
	Transform transform;
	Model* model = nullptr;
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	Texture* texture = nullptr;
	//TODO: decide how to do collisions
	//	Collider* collider = nullptr;
};