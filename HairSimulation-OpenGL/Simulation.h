#pragma once
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "FTL.h"
#include "HairyModel.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "AntTweakBar\AntTweakBar.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void Update();
	void Draw();
private:
	Camera* camera;

	std::vector<Shader*> shaders;
	std::vector<GameObject*> gameObjects;
	std::vector<HairyModel*> hairyModels;
	std::vector<SphereCollider> colliders;

	std::vector<ftl::FTL*> ftl;

	TwBar *mainBar;

	Vector3 windDir = Vector3(1, 0, 0);
	float windForce = 1.0f;
	float gravForce = 0.1f;

	bool enableWind = false;
	bool enableGravity = true;
	bool showColliders = false;
	bool showHair = false;
	bool showInstancedHair = false;
};

