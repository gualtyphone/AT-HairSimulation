#include "Simulation.h"
#include <math.h>
#include "guicon.h"
#include "Input.h"
#include "Random.h"

//This is the start for the simulation code which will all be platform independent because we hide all the platform
//specific code in main and the equivalent of the GLUT that i'll write

//We cannot use normal main because that will override WinMain loading
//Fake starting point
Simulation::Simulation()
{
	std::cout << "HI";
	shader = new Shader(std::string("./resources/shaders/basicShader"));
	
	
	Vertex vertices[] = { Vertex(Vector3(-0.5, -0.5, 0), Vector2(0.0, 0.0)),
						  Vertex(Vector3(0, 0.5, 0)    , Vector2(1.0, 0.0)),
						  Vertex(Vector3(0.5, -0.5, 0) , Vector2(0.0, 1.0))};
	unsigned int indices[] { 0, 1, 2 };
	mesh = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	texture = new Texture("./resources/textures/bricks.jpg", "texture_diffuse");
	texture2 = new Texture("./resources/textures/bricks.jpg", "texture_diffuse");

	model2 = new Model("./resources/models/monkey3.obj");
	model300 = new HairyModel("./resources/models/Cap300.obj");
	model = new Model("./resources/models/TheRock/TheRock2.obj");

	model300->AddHair();

	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(.1, .1, .1));
	transform2 = new Transform(Vector3(-5, 0, 20), Vector3(0, 0, 0), Vector3(1, 1, 1));

	camera = new Camera(Vector3(0, 0, 30), 1.0f, (float)800 / (float)600, 0.01f, 1000.0f);

	/*for (int i = 0; i < 300; i++)
	{
		ftl.push_back(new ftl::FTL());
		ftl[i]->setup(10, Vector3(0, 00.5f, 0), Vector3((float)(i-150)/50.0f, 0, 0));
	}*/
	
	
}

Simulation::~Simulation()
{

}

void Simulation::Tick()
{

}
float counter = 0.0f;

void Simulation::Draw()
{
	float sinCount = sin(counter);
	float cosCount = cos(counter);
	transform->SetPosition(Vector3(sinf(counter), 0, 0));
	transform->SetRotation(Vector3(cosCount, sinCount, 0));
	//transform->SetScale(Vector3(cosCount, cosCount, cosCount));

	if (Input::GetKey(KeyCode::A))
	{
		for (int i = 0; i < 300; i++)
		{
			ftl[i]->addForce(Vector3(-Random::Range(0.4f, 0.6f), 0, 0));
		}
	}
	if (Input::GetKey(KeyCode::S))
	{
		transform2->Move(Vector3(0, 0, -0.5f));
	}
	if (Input::GetKey(KeyCode::D))
	{
		for (int i = 0; i < 300; i++)
		{
			ftl[i]->addForce(Vector3(Random::Range(0.4f, 0.6f),0 , 0));
		}
	}
	/*for (int i = 0; i < 300; i++)
	{
		ftl[i]->addForce(Vector3(0, -0.15f, 0));
	}
	*/
	if (Input::GetKey(KeyCode::W))
	{
		transform2->Move(Vector3(0, 0, 0.5f));
	}

	if (Input::GetKey(KeyCode::L))
	{
		camera->Move(Vector3(0.5f, 0, 0));
	}
	if (Input::GetKey(KeyCode::K))
	{
		camera->Move(Vector3(0, 0, 0.5f));
	}
	if (Input::GetKey(KeyCode::J))
	{
		camera->Move(Vector3(-0.5f, 0, 0));
	}
	if (Input::GetKey(KeyCode::I))
	{
		camera->Move(Vector3(0, 0, -0.5f));
	}

	if (Input::GetKey(KeyCode::U))
	{
		camera->Move(Vector3(0, -0.1f, 0));
	}
	if (Input::GetKey(KeyCode::O))
	{
		camera->Move(Vector3(0, 0.1f, 0));
	}


	if (Input::GetKey(KeyCode::Q))
	{
		transform->Move(Vector3(0, -0.1f, 0));
	}
	if (Input::GetKey(KeyCode::E))
	{
		transform->Move(Vector3(0, 0.1f, 0));
	}

	shader->Bind();
	
	shader->Update(*transform, *camera);
	//texture->Bind(0);
	model->Draw();
	model300->Draw();

	texture2->Bind(0);
	shader->Update(*transform2, *camera);
	model2->Draw();


	//for (int i = 0; i < 300; i++)
	//{
	//	ftl[i]->update();
	//	ftl[i]->draw();
	//}
	

	counter += 0.01f;
}
