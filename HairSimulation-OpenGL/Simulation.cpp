#include "Simulation.h"
#include <math.h>
//This is the start for the simulation code which will all be platform independent because we hide all the platform
//specific code in main and the equivalent of the GLUT that i'll write

//We cannot use normal main because that will override WinMain loading
//Fake starting point
Simulation::Simulation()
{
	shader = new Shader(std::string("./resources/shaders/basicShader"));
	
	
	Vertex vertices[] = { Vertex(Vector3(-0.5, -0.5, 0), Vector2(0.0, 0.0)),
						  Vertex(Vector3(0, 0.5, 0)    , Vector2(1.0, 0.0)),
						  Vertex(Vector3(0.5, -0.5, 0) , Vector2(0.0, 1.0))};
	unsigned int indices[] { 0, 1, 2 };
	//mesh = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	texture = new Texture("./resources/textures/bricks.jpg");

	model = new Model("./resources/models/TheRock/TheRock2.obj");
}

Simulation::~Simulation()
{

}

void Simulation::Tick()
{

}

void Simulation::Draw()
{
	
	shader->Bind();
	texture->Bind(0);
	//mesh->Draw();
	model->Draw();

}
