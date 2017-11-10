#ifndef ROXLU_FTL_H
#define ROXLU_FTL_H

#include "GMath.h"
#include <vector>

namespace ftl
{

	struct Particle
	{
		Particle(GMath::Vector3 position, float m);
		GMath::Vector3 position;
		GMath::Vector3 tmp_position;
		GMath::Vector3 forces;
		GMath::Vector3 velocity;
		GMath::Vector3 d;
		float mass;
		float inv_mass;
		bool enabled;

	};

	class FTL
	{
	public:
		FTL();
		void setup(int num, GMath::Vector3 d, GMath::Vector3 pos);
		void addForce(GMath::Vector3 f);
		void update();
		void draw();
	public:
		float len;
		std::vector<Particle*> particles;
		GMath::Vector3 color;
	};

}
#endif