#include "HairyModel.h"
#include "Input.h"
#include "Random.h"
#include <algorithm>


HairyModel::HairyModel(std::string fileName)
	: Model(fileName)
{}

void HairyModel::AddHair(Transform* transform)
{
	for each (Mesh* mesh in meshes)
	{
		for each (Vertex vert in mesh->vertices)
		{
			if (std::find_if(hair.begin(), hair.end(), [&vert](ftl::FTL* strand){
				return strand->originalPos == *vert.GetPos();
			}) != hair.end())
			{
				/* v contains x */
				int i = 0;
			}
			else
			{
				/* v does not contain x */
				hair.push_back(new ftl::FTL());
				hair[hair.size() - 1]->setup(30, (*vert.GetNormal())/2, *vert.GetPos(), transform);
			}			
		}
	}
}

void HairyModel::Draw()
{
	//if (Input::GetKey(KeyCode::D))
	//{
	//	for (int i = 0; i < hair.size(); i++)
	//	{
	//		hair[i]->addForce(Vector3(Random::Range(0.4f, 0.6f), 0, 0));
	//	}
	//}
	//Model::Draw();
	for (int i = 0; i < hair.size(); i++)
	{
		hair[i]->update();
		hair[i]->draw();
	}
}

void HairyModel::Collide(SphereCollider coll)
{
	for each (auto strand in hair)
	{
		strand->Collide(coll);
	}

}
