#include "Simulation.h"
#include <math.h>
#include "guicon.h"

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

	model = new Model("./resources/models/monkey3.obj");

	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	camera = new Camera(Vector3(0, 0, 10), 1.4, (float)800 / (float)600, 0.01f, 100.0f);
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
	//transform->SetRotation(Vector3(cosCount, sinCount, 0));
	//transform->SetScale(Vector3(cosCount, cosCount, cosCount));

	shader->Bind();
	texture->Bind(0);
	shader->Update(*transform, *camera);
	//mesh->Draw();
	model->Draw();

	counter += 0.01f;
}
