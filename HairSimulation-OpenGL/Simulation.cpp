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
	camera = new Camera(Vector3(0, 0, 30), 1.0f, (float)800 / (float)600, 0.01f, 1000.0f);
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
						  nullptr, shaders[0]));

	SphereCollider coll;
	coll.radius = 8.5f;
	coll.transform.SetPosition(Vector3(0, 4.5f, -4.0f));
	colliders.push_back(coll);

	SphereCollider lowerFace;
	lowerFace.radius = 7.5f;
	lowerFace.transform.SetPosition(Vector3(0, -2.0f, 0.0f));
	colliders.push_back(lowerFace);


	SphereCollider coll2;
	coll2.radius = 3.0f;
	coll2.transform.SetPosition(Vector3(2.0f, 4.0f, 2.0F));
	colliders.push_back(coll2);

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

	for (int i = 0; i < colliders.size(); i++)
	{
		shaders[0]->Update(colliders[i].transform);
		colliders[i].draw();
	}

	


	//shaders[1]->Bind();
	//shaders[1]->Update(Transform());
	//for (int i = 0; i < 100; i++)
	//{
	//	ftl[i]->update();
	//	ftl[i]->draw();
	//}


	//shaders[0]->Update(cyl.transform);
	//cyl.Draw();
}
