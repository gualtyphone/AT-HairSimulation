#pragma once
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Transform.h"


class Simulation
{
public:
	Simulation();
	~Simulation();

	void Tick();
	void Draw();
private:
	Shader* shader;
	Texture* texture;
	Transform* transform;
	Mesh* mesh;
	Model* model;
};

