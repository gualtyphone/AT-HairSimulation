#include "FTL.h"
#include <math.h>
#include "GL\glew.h"
#include "Random.h"

namespace ftl
{

	Particle::Particle(GMath::Vector3 p, float m)
		:position(p)
		, tmp_position(p)
		, enabled(true)
	{

		if (m < 0.001)
		{
			m = 0.001;
		}

		mass = m;
		inv_mass = 1.0 / mass;
	}

	// ------------------------

	FTL::FTL()
		:len(10)
	{}

	void FTL::setup(int num, GMath::Vector3 dir, GMath::Vector3 pos)
	{
		float dim = 50;
		len = dir.magnitude();
		//GMath::Vector3 pos(0, 0, 0);
		float mass = Random::Range(0.2f, 0.8f);
		for (int i = 0; i < num; ++i)
		{
			Particle* p = new Particle(pos, mass); //rx_random(1.0f, 10.0f));
			particles.push_back(p);
			pos = pos + dir;
		}

		particles[0]->enabled = false;
	}

	void FTL::addForce(GMath::Vector3 f)
	{
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			Particle* p = *it;
			if (p->enabled)
			{
				p->forces = p->forces + f;
			}
		}
	}

	void FTL::update()
	{
		float dt = 1.0f / 20.0f;

		// update velocities
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			Particle* p = *it;
			if (!p->enabled)
			{
				p->tmp_position = p->position;
				continue;
			}
			p->velocity = p->velocity + (p->forces * p->inv_mass) * dt;
			p->tmp_position  = p->tmp_position + (p->velocity * dt);
			p->forces = GMath::Vector3();
			p->velocity = p->velocity * 0.99;
		}

		// solve constraints
		GMath::Vector3 dir;
		GMath::Vector3 curr_pos;
		for (size_t i = 1; i < particles.size(); ++i)
		{
			Particle* pa = particles[i - 1];
			Particle* pb = particles[i];
			curr_pos = pb->tmp_position;
			dir = pb->tmp_position - pa->tmp_position;
			dir.normalize();
			pb->tmp_position = pa->tmp_position + dir * len;
			pb->d = curr_pos - pb->tmp_position; //  - curr_pos;
		}

		for (size_t i = 1; i < particles.size(); ++i)
		{
			Particle* pa = particles[i - 1];
			Particle* pb = particles[i];
			if (!pa->enabled)
			{
				continue;
			}
			pa->velocity = ((pa->tmp_position - pa->position) / dt) + (pb->d / dt) * 0.9f;
			pa->position = pa->tmp_position;
		}

		Particle* last = particles.back();
		last->position = last->tmp_position;

	}

	void FTL::draw()
	{

		glLineWidth(0.1f);
		glBegin(GL_LINE_STRIP);
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			Particle* p = *it;

			if (!p->enabled)
			{
				glColor3f(1.0f, .2f, .2f);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}

			glVertex3f(p->position.GetX(), p->position.GetY(), p->position.GetZ());
		}
		glEnd();
		glFlush();
	}

}