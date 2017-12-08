#include "Simulation.h"
#include <math.h>
#include "guicon.h"
#include "Input.h"
#include "Random.h"

#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Lighting.h"

#include "AntTweakBar\AntTweakBar.h"
//This is the start for the simulation code which will all be platform independent because we hide all the platform
//specific code in main and the equivalent of the GLUT that i'll write

//We cannot use normal main because that will override WinMain loading
//Fake starting point
Simulation::Simulation()
{
	TwInit(TW_OPENGL, NULL);

	TwWindowSize(Display::getDisplay()->GetSize().x, Display::getDisplay()->GetSize().y);

	mainBar = TwNewBar("Controls");
	TwAddVarRW(mainBar, "Enable Wind", TW_TYPE_BOOL8, &enableWind, "");
	TwAddVarRW(mainBar, "Wind Direction", TW_TYPE_DIR3F, &windDir, "");
	TwAddVarRW(mainBar, "Wind Strength", TW_TYPE_FLOAT, &windForce, "step=0.01");
	TwAddSeparator(mainBar, NULL, "");
	TwAddVarRW(mainBar, "Enable Gravity", TW_TYPE_BOOL8, &enableGravity, "");
	TwAddVarRW(mainBar, "Gravity Strength", TW_TYPE_FLOAT, &gravForce, "step=0.01");

	TwAddSeparator(mainBar, NULL, "");
	TwAddVarRW(mainBar, "Light Direction", TW_TYPE_DIR3F, Lighting::GetLight(), "");
	TwAddSeparator(mainBar, NULL, "");
	TwAddVarRW(mainBar, "Draw Hair", TW_TYPE_BOOL8, &showHair, "");
	TwAddVarRW(mainBar, "Draw InstancedHair", TW_TYPE_BOOL8, &showInstancedHair, "");
	TwAddVarRW(mainBar, "Draw Colliders", TW_TYPE_BOOL8, &showColliders, "");

	camera = new Camera(Vector3(0, 0, -30), 1.0f, (float)800 / (float)600, 0.01f, 1000.0f);
	shaders.push_back(new Shader(std::string("./resources/shaders/basicShader"), camera));
	shaders.push_back(new Shader(std::string("./resources/shaders/instancedHairShader"), camera));


	gameObjects.push_back(new GameObject("Monkey",
						  Transform(Vector3(-5, 0, 20), Vector3(0, 0, 0), Vector3(1, 1, 1)),
						  new Model("./resources/models/monkey3.obj"),
						  nullptr, shaders[0],
						  new Texture("./resources/textures/bricks.jpg", "texture_diffuse")));

	gameObjects.push_back(new GameObject("TheRock",
						  Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(.1f, .1f, .1f)),
						  new Model("./resources/models/TheRock/TheRock2.obj"),
						  nullptr, shaders[0]));

	HairyModel* model = new HairyModel("./resources/models/Cap300.obj", shaders[1]);
	model->AddHair(gameObjects[1]->GetTransform());
	gameObjects.push_back(new GameObject("TheRock", Transform(),
						  model,
						  nullptr, shaders[1]));

	hairyModels.push_back(model);

	SphereCollider head;
	head.radius = 8.9f;
	head.transform.SetPosition(Vector3(0, 35.0f, -58.0f));
	head.parent = gameObjects[1]->GetTransform();
	colliders.push_back(head);

	SphereCollider foreHead;
	foreHead.radius = 7.5f;
	foreHead.transform.SetPosition(Vector3(0, 47.0f, -23));
	foreHead.parent = gameObjects[1]->GetTransform();
	colliders.push_back(foreHead);

	SphereCollider centerHead;
	centerHead.radius = 7.5f;
	centerHead.transform.SetPosition(Vector3(0, 54, -38));
	centerHead.parent = gameObjects[1]->GetTransform();
	colliders.push_back(centerHead);

	SphereCollider lowerFace;
	lowerFace.radius = 7.5f;
	lowerFace.transform.SetPosition(Vector3(0, -20, 0));
	lowerFace.parent = gameObjects[1]->GetTransform();
	colliders.push_back(lowerFace);

	SphereCollider neck;
	neck.radius = 6.5f;
	neck.transform.SetPosition(Vector3(0, -70, -20));
	neck.parent = gameObjects[1]->GetTransform();
	colliders.push_back(neck);

	SphereCollider eyeRight;
	eyeRight.radius = 3.0f;
	eyeRight.transform.SetPosition(Vector3(20, 40, 30));
	eyeRight.parent = gameObjects[1]->GetTransform();
	//colliders.push_back(eyeRight);

	SphereCollider eyeLeft;
	eyeLeft.radius = 3.0f;
	eyeLeft.transform.SetPosition(Vector3(-20, 40, 30));
	eyeLeft.parent = gameObjects[1]->GetTransform();
	//colliders.push_back(eyeLeft);

	SphereCollider earRight;
	earRight.radius = 3.6f;
	earRight.transform.SetPosition(Vector3(90, -02, -45));
	earRight.parent = gameObjects[1]->GetTransform();
	colliders.push_back(earRight);

	SphereCollider earLeft;
	earLeft.radius = 3.6f;
	earLeft.transform.SetPosition(Vector3(-90, -02, -45));
	earLeft.parent = gameObjects[1]->GetTransform();
	colliders.push_back(earLeft);

	SphereCollider nose;
	nose.radius = 2.5f;
	nose.transform.SetPosition(Vector3(0, 7, 60));
	nose.parent = gameObjects[1]->GetTransform();
	//colliders.push_back(nose);

	SphereCollider wind;
	wind.radius = 12.0f;
	wind.transform.SetPosition(Vector3(0, 0, 120));
	wind.parent = gameObjects[1]->GetTransform();
	colliders.push_back(wind);


	for (int i = 0; i < colliders.size(); i++)
	{
		model->AddCollider(&colliders[i]);
	}

	for (int i = 0; i < 100; i++)
	{
		ftl.push_back(new ftl::FTL());
		ftl[ftl.size() - 1]->setup(30, Vector3(0, -1, 0), Vector3((i - 50) / 10.0f, 0, 0));
	}
}

Simulation::~Simulation()
{
	TwTerminate();
}

void Simulation::Update()
{
	camera->Update();

	for each (auto& go in gameObjects)
	{
		go->Update();
	}

	if (Input::GetKey(KeyCode::U))
	{
		showColliders = true;
	}
	if (Input::GetKey(KeyCode::H))
	{
		showColliders = false;
	}

	if (enableWind)
	{
		for each (auto HM in hairyModels)
		{
			HM->AddForce(windDir + Random::Vec3(-1.0f, 1.0f), windForce);
		}
	}

	if (enableGravity)
	{
		for each (auto HM in hairyModels)
		{
			HM->AddForce(Vector3(0, -1, 0), gravForce);
		}
	}

	if (Input::GetKey(KeyCode::J))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(-0.1f, 0.0f, 0.0f));
		}
		gameObjects[1]->GetTransform()->Move(Vector3(-0.1f, 0.0f, 0.0f));
		//gameObjects[2]->GetTransform()->Move(Vector3(-0.1f, 0.0f, 0.0f));
	}
	if (Input::GetKey(KeyCode::L))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.1f, 0.0f, 0.0f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.1f, 0.0f, 0.0f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.1f, 0.0f, 0.0f));
	}
	if (Input::GetKey(KeyCode::K))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.0f, 0.0f, -0.1f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.0f, 0.0f, -0.1f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.0f, 0.0f, -0.1f));
	}
	if (Input::GetKey(KeyCode::I))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.0f, 0.0f, 0.1f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.0f, 0.0f, 0.1f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.0f, 0.0f, 0.1f));
	}
}

void Simulation::Draw()
{
	shaders[0]->Bind();
	for each (auto& go in gameObjects)
	{
		go->Draw();
	}

	if (showColliders)
	{

		for (int i = 0; i < colliders.size(); i++)
		{
			shaders[0]->Update(colliders[i].parent->Get() * colliders[i].transform.Get() );
			colliders[i].draw();
		}

	}

	//TwDraw();
}
