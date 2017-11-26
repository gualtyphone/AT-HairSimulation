#pragma once
#include "Model.h";
#include <vector>;
#include "FTL.h";
#include "SphereCollider.h"


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
protected:
private:
	std::vector<ftl::FTL*> hair;
	std::vector<SphereCollider*> colliders;
	Shader* shaderPtr;
};

