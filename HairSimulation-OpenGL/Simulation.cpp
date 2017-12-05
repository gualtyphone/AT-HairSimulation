#include "Simulation.h"
#include <math.h>
#include "guicon.h"
#include "Input.h"
#include "Random.h"

#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
//This is the start for the simulation code which will all be platform independent because we hide all the platform
//specific code in main and the equivalent of the GLUT that i'll write

//We cannot use normal main because that will override WinMain loading
//Fake starting point
Simulation::Simulation()
{
	camera = new Camera(Vector3(0, 0, -30), 1.0f, (float)800 / (float)600, 0.01f, 1000.0f);
	shaders.push_back(new Shader(std::string("./resources/shaders/basicShader"), camera));
	shaders.push_back(new Shader(std::string("./resources/shaders/instancedHairShader"), camera));


	gameObjects.push_back(new GameObject("Monkey",
						  Transform(Vector3(-5, 0, 20), Vector3(0, 0, 0), Vector3(1, 1, 1)),
						  new Model("./resources/models/monkey3.obj"),
						  nullptr, shaders[0],
						  new Texture("./resources/textures/bricks.jpg", "texture_diffuse")));

	gameObjects.push_back(new GameObject("TheRock",
						  Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(.1, .1, .1)),
						  new Model("./resources/models/TheRock/TheRock2.obj"),
						  nullptr, shaders[0]));

	HairyModel* model = new HairyModel("./resources/models/Cap300.obj", shaders[1]);
	model->AddHair(gameObjects[1]->GetTransform());
	gameObjects.push_back(new GameObject("TheRock", Transform(),
						  model,
						  nullptr, shaders[1]));

	SphereCollider head;
	head.radius = 8.9f;
	head.transform.SetPosition(Vector3(0, 3.5f, -5.8f));
	colliders.push_back(head);

	SphereCollider foreHead;
	foreHead.radius = 7.5f;
	foreHead.transform.SetPosition(Vector3(0, 4.7f, -2.3));
	colliders.push_back(foreHead);

	SphereCollider centerHead;
	centerHead.radius = 7.5f;
	centerHead.transform.SetPosition(Vector3(0, 5.4f, -3.8));
	colliders.push_back(centerHead);

	SphereCollider lowerFace;
	lowerFace.radius = 7.5f;
	lowerFace.transform.SetPosition(Vector3(0, -2.0f, 0.0f));
	colliders.push_back(lowerFace);

	SphereCollider neck;
	neck.radius = 6.5f;
	neck.transform.SetPosition(Vector3(0, -7.0f, -2.0f));
	colliders.push_back(neck);

	SphereCollider eyeRight;
	eyeRight.radius = 3.0f;
	eyeRight.transform.SetPosition(Vector3(2.0f, 4.0f, 3.0f));
	//colliders.push_back(eyeRight);

	SphereCollider eyeLeft;
	eyeLeft.radius = 3.0f;
	eyeLeft.transform.SetPosition(Vector3(-2.0f, 4.0f, 3.0f));
	//colliders.push_back(eyeLeft);

	SphereCollider earRight;
	earRight.radius = 2.6f;
	earRight.transform.SetPosition(Vector3(7.0f, -0.2f, -4.5f));
	colliders.push_back(earRight);

	SphereCollider earLeft;
	earLeft.radius = 2.6f;
	earLeft.transform.SetPosition(Vector3(-7.0f, -0.2f, -4.5f));
	colliders.push_back(earLeft);

	SphereCollider nose;
	nose.radius = 2.5f;
	nose.transform.SetPosition(Vector3(0.0f, 0.7f, 6.0f));
	colliders.push_back(nose);

	SphereCollider wind;
	wind.radius = 12.0f;
	wind.transform.SetPosition(Vector3(0.0f, 0.0f, 12.0f));
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

}

void Simulation::Update()
{
	//for each (auto& go in gameObjects)
	//{
	//	go->Update();
	//}

	if (Input::GetKey(KeyCode::U))
	{
		showColliders = true;
	}
	if (Input::GetKey(KeyCode::H))
	{
		showColliders = false;
	}
}

void Simulation::Draw()
{
	if (Input::GetKey(KeyCode::J))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(-0.1f, 0.0f, 0.0f));
		}
		gameObjects[1]->GetTransform()->Move(Vector3(-0.4f, 0.0f, 0.0f));
		//gameObjects[2]->GetTransform()->Move(Vector3(-0.1f, 0.0f, 0.0f));
	}
	if (Input::GetKey(KeyCode::L))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.1f, 0.0f, 0.0f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.4f, 0.0f, 0.0f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.1f, 0.0f, 0.0f));
	}
	if (Input::GetKey(KeyCode::K))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.0f, 0.0f, -0.1f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.0f, 0.0f, -0.4f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.0f, 0.0f, -0.1f));
	}
	if (Input::GetKey(KeyCode::I))
	{
		for (int i = 0; i < 100; i++)
		{
			ftl[i]->addForce(Vector3(0.0f, 0.0f, 0.1f));

		}
		gameObjects[1]->GetTransform()->Move(Vector3(0.0f, 0.0f, 0.4f));
		//gameObjects[2]->GetTransform()->Move(Vector3(0.0f, 0.0f, 0.1f));
	}

	camera->Update();

	shaders[0]->Bind();
	for each (auto& go in gameObjects)
	{
		go->Draw();
	}

	if (showColliders)
	{

		for (int i = 0; i < colliders.size(); i++)
		{
			shaders[0]->Update(colliders[i].transform);
			colliders[i].draw();
		}

	}
}
