#pragma once
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "FTL.h"
#include "HairyModel.h"
#include "SphereCollider.h"

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
	Transform* transform3;
	Transform* transform4;
	Mesh* mesh;
	Model* model;
	Model* model2;
	HairyModel* model300;
	Camera* camera;
	std::vector<ftl::FTL*> ftl;
	SphereCollider head;
};

