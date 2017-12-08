#include "HairyModel.h"
#include "Input.h"
#include "Random.h"
#include "Lighting.h"
#include <algorithm>

void TW_CALL ApplyHairSettings(void *clientData)
{
	HairyModel* hm = (HairyModel*)clientData;
	hm->ApplySettings();

	_RPT0(_CRT_ERROR, "Applying Settings\n");
}

HairyModel::HairyModel(std::string fileName, Shader* shader)
	: Model(fileName)
{
	shaderPtr = shader;
	hairBar = TwNewBar("Hairs");

	TwAddVarRW(hairBar, "Draw Hair", TW_TYPE_BOOL8, &drawHair, "");
	TwAddVarRW(hairBar, "Draw Instanced Hair", TW_TYPE_BOOL8, &drawInstancedHair, "");
	TwAddSeparator(hairBar, NULL, "");
	TwAddVarRW(hairBar, "Color", TW_TYPE_COLOR4F, &hairColor, "");
	TwAddVarRW(hairBar, "Color Variation", TW_TYPE_FLOAT, &colorVariation, "step=0.01");
	TwAddSeparator(hairBar, NULL, "");
	TwAddVarRW(hairBar, "Hair Segments", TW_TYPE_INT16, &hairSegments, "");
	TwAddVarRW(hairBar, "Hair Segment Length", TW_TYPE_FLOAT, &hairLength, "step=0.01");
	TwAddVarRW(hairBar, "Hair Instances", TW_TYPE_INT16, &instancedHairNumber, "");
	TwAddVarRW(hairBar, "Hair Instances Distance", TW_TYPE_FLOAT, &instancedHairDist, "step=0.01");
	TwAddSeparator(hairBar, NULL, "");
	TwAddVarRW(hairBar, "Hair Stiffness", TW_TYPE_FLOAT, &hairStiffness, "step=0.01");

	TwAddButton(hairBar, "Apply", ApplyHairSettings, this , "");
	
}

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
				std::vector<Vector3> instancePositions;
				for (int i = 0; i < 100/*hairThickness*/; i++)
				{
					instancePositions.push_back(Vector3(Random::Range(-1, 1), Random::Range(-1, 1), Random::Range(-1, 1)));
				}
				/* v does not contain x */
				hair.push_back(new ftl::FTL());
				hair[hair.size() - 1]->setup(30, (*vert.GetNormal())/2, *vert.GetPos(), instancePositions, transform);
			}			
		}
	}
}

void HairyModel::Draw()
{
	for each (auto collider in colliders)
	{
		Collide(*collider);
	}
	shaderPtr->Update(Transform(), *Lighting::GetLight()) ;
	shaderPtr->Bind();
	if (Input::GetKey(KeyCode::F))
	{
		drawHair = false;
	}

	if (Input::GetKey(KeyCode::T))
	{
		drawHair = true;
	}

	if (drawHair)
	{
		for (int i = 0; i < hair.size(); i++)
		{
			hair[i]->update();
			hair[i]->draw(drawInstancedHair);
		}
	}
}

void HairyModel::Collide(SphereCollider& coll)
{
	for each (auto strand in hair)
	{
		strand->Collide(coll);
	}
}

void HairyModel::AddForce(Vector3 force, float strength = 1.0f)
{
	force.normalize();
	Vector3	newForce = force * strength;
	for each (auto strand in hair)
	{
		strand->addForce(newForce);
	}
}

void HairyModel::ApplySettings()
{
	for each (auto strand in hair)
	{
		strand->SetNumberOfParticles(hairSegments);
		CreateAndUpdateInstances(strand);
		strand->SetColors(hairColor, colorVariation);
		strand->len = hairLength;
	}
}

void HairyModel::CreateAndUpdateInstances(ftl::FTL* strand)
{
	std::vector<Vector3> instancePositions;
	for (int i = 0; i < instancedHairNumber; i++)
	{
		instancePositions.push_back(Random::Vec3(-instancedHairDist, instancedHairDist));
	}

	strand->SetInstances(instancePositions);
}
