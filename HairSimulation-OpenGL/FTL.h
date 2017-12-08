#ifndef ROXLU_FTL_H
#define ROXLU_FTL_H

#include "GMath.h"
#include <vector>
#include "Transform.h"
#include "SphereCollider.h"

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
		void setup(int num, GMath::Vector3 d, GMath::Vector3 pos, Transform* follow = nullptr);
		void setup(int num, GMath::Vector3 d, GMath::Vector3 pos, std::vector<Vector3> instancesPos, Transform* follow = nullptr);
		void addForce(GMath::Vector3 f);
		void update();
		void draw();

		void Collide(SphereCollider& coll);

	public:
		float len;
		GMath::Vector3 pos;
		GMath::Vector3 originalPos;
		Transform* follow;
		std::vector<Particle*> particles;
		GMath::Vector3 color;

		std::vector<Vector3> positions;
		std::vector<Vector3> directions;
		std::vector<GLuint> indicies;
		std::vector<Vector3> instances;
		std::vector<Vector4> colors;
		GLuint m_vertexArrayBuffers[5];
		GLuint m_vertexArrayObject;
		unsigned int m_drawCount;

		bool instance = false;
	};

}
#endif