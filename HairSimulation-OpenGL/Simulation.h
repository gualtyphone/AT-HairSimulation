#pragma once
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "FTL.h"


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
	Texture* texture2;
	Transform* transform;
	Transform* transform2;
	Mesh* mesh;
	Model* model;
	Model* model2;
	Camera* camera;
	std::vector<ftl::FTL*> ftl;
};

