#pragma once
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"


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
	Mesh* mesh;
	Model* model;
};

