#pragma once
#include "Model.h";
#include <vector>;
#include "FTL.h";


class HairyModel : Model
{
public:
	HairyModel(std::string fileName);
	HairyModel::~HairyModel()
	{}

	void AddHair();

	virtual void Draw() override;

protected:
private:
	std::vector<ftl::FTL*> hair;
};

