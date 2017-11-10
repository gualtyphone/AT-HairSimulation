#include "HairyModel.h"



HairyModel::HairyModel(std::string fileName)
	: Model(fileName)
{}

void HairyModel::AddHair()
{
	for each (Mesh* mesh in meshes)
	{
		for each (Vertex vert in mesh->vertices)
		{
			hair.push_back(new ftl::FTL());
			hair[hair.size()-1]->setup(10, *vert.GetNormal(), *vert.GetPos());
		}
	}
}

void HairyModel::Draw()
{
	//Model::Draw();
	for (int i = 0; i < hair.size(); i++)
	{
		hair[i]->update();
		hair[i]->draw();
	}
}