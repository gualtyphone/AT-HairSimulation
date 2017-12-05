#pragma once
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "FTL.h"
#include "HairyModel.h"
#include "SphereCollider.h"
//#include "CylinderCollider.h"
#include "GameObject.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void Update();
	void Draw();
private:
	std::vector<Shader*> shaders;
	std::vector<GameObject*> gameObjects;
	Camera* camera;

	Texture* golden;

	std::vector<ftl::FTL*> ftl;
	std::vector<SphereCollider> colliders;
	bool showColliders = false;
	//CylinderCollider cyl;
};

