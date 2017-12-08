#pragma once
#include "Model.h"
#include <vector>
#include "FTL.h"
#include "SphereCollider.h"
#include "AntTweakBar\AntTweakBar.h"


class HairyModel : public Model
{
public:
	HairyModel(std::string fileName, Shader* shader);
	HairyModel::~HairyModel()
	{}

	void AddHair(Transform* transform = nullptr);

	virtual void Draw() override;

	virtual void Collide(SphereCollider&  coll);
	inline void AddCollider(SphereCollider* coll)
	{
		colliders.push_back(coll);
	}

	void AddForce(Vector3 force, float strength);

	void ApplySettings();

	void CreateAndUpdateInstances(ftl::FTL* strand);

protected:
private:
	std::vector<ftl::FTL*> hair;
	std::vector<SphereCollider*> colliders;
	Shader* shaderPtr;

	bool drawHair = false;
	bool drawInstancedHair = false;

	Vector4 hairColor = Vector4(200.0f/ 255.0f, 180.0f / 255.0f, 80.0f / 255.0f, 1.0f);
	float colorVariation = 0.1f;

	int hairSegments = 30;
	float hairLength = 0.5f;
	int instancedHairNumber = 100;
	float instancedHairDist = 1.0f;

	float hairStiffness = 1.0f;

	TwBar *hairBar;
};

