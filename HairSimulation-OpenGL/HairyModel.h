#pragma once
#include "Model.h";
#include <vector>;
#include "FTL.h";
#include "SphereCollider.h"


class HairyModel : Model
{
public:
	HairyModel(std::string fileName);
	HairyModel::~HairyModel()
	{}

	void AddHair(Transform* transform = nullptr);

	virtual void Draw() override;

	virtual void Collide(SphereCollider  coll);
	
protected:
private:
	std::vector<ftl::FTL*> hair;
};

