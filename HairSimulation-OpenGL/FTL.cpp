#include "FTL.h"
#include <math.h>
#include "GL\glew.h"
#include "Random.h"
#include "Input.h"

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

	void FTL::setup(int num, GMath::Vector3 dir, GMath::Vector3 _pos, Transform* _follow)
	{
		std::vector<Vector3> instancesPos;
		for (GLuint i = 0; i < 100; i++)
		{
			instancesPos.push_back(Vector3(Random::Range(-10, 10), 0, 0));
		}
		setup(num, dir, _pos, instancesPos, follow);
	}

	void FTL::setup(int num, GMath::Vector3 _dir, GMath::Vector3 _pos, std::vector<Vector3> instancesPos, Transform* _follow)
	{
		pos = _pos;

		originalPos = _pos;

		follow = _follow;

		if (follow != nullptr)
		{
			pos = GMath::transformPoint(originalPos, follow->Get());
		}
		float dim = 50;
		len = _dir.magnitude();
		originalDir = _dir;
		//GMath::Vector3 pos(0, 0, 0);
		float mass = Random::Range(0.2f, 0.8f);
		for (int i = 0; i < num; ++i)
		{
			Particle* p = new Particle(pos, mass); //rx_random(1.0f, 10.0f));
			particles.push_back(p);
			pos = pos + originalDir;
		}

		particles[0]->enabled = false;

		m_drawCount = particles.size();

		
		//create vertex array
		glGenVertexArrays(1, &m_vertexArrayObject);
		//load vertex array
		glBindVertexArray(m_vertexArrayObject);

		

		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			positions.push_back((*it)->position);
		}

		for (int i = 0; i < particles.size()-1; i++)
		{
			directions.push_back(particles[i+1]->position - particles[i]->position);
		}
		directions.push_back(particles[particles.size()-1]->position - particles[particles.size() -2]->position);

		for (GLuint i = 0; i < positions.size(); i++)
		{
			indicies.push_back(i);
		}
		
		instances.push_back(Vector3(0, 0, 0));
		for (GLuint i = 1; i < instancesPos.size(); i++)
		{
			instances.push_back(instancesPos[i]);
		}

		for (GLuint i = 0; i < instances.size(); i++)
		{
			colors.push_back(Vector4(Random::Range(200, 210)/255.0f, Random::Range(180, 190)/255.0f, Random::Range(80, 90)/255.0f, 1.0f));
		}

		//Vertices
		glGenBuffers(5, m_vertexArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Instanced Positions
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
		glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(instances[0]), &instances[0], GL_DYNAMIC_DRAW);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Instanced Colors
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Directions
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[3]);
		glBufferData(GL_ARRAY_BUFFER, directions.size() * sizeof(directions[0]), &directions[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Indicies
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[4]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(indicies[0]), &indicies[0], GL_DYNAMIC_DRAW);


		glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
		glVertexAttribDivisor(2, 1); // color : one per quad -> 1
		glVertexAttribDivisor(3, 0); // directions : always the same
		//clear loaded vertex array
		glBindVertexArray(0);
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

		if (follow != nullptr)
		{
			particles[0]->position = GMath::transformPoint(originalPos, follow->Get());
		}

		// update velocities
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			Particle* p = *it;
			if (!p->enabled)
			{
				p->tmp_position = p->position;
				continue;
			}
			p->velocity = p->velocity + (p->forces * p->inv_mass) /** dt*/;
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
			pa->velocity = ((pa->tmp_position - pa->position) / dt) + (pb->d / dt) * .9f;
			pa->position = pa->tmp_position;
		}

		Particle* last = particles.back();
		last->position = last->tmp_position;

	}

	void FTL::draw(bool instance)
	{
		//This could definetly be improved
		positions.clear();
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			positions.push_back((*it)->position);
		}

		directions.clear();
		for (int i = 0; i < particles.size() - 1; i++)
		{
			directions.push_back(particles[i + 1]->position - particles[i]->position);
		}
		directions.push_back(particles[particles.size() - 1]->position - particles[particles.size() - 2]->position);

		glBindVertexArray(m_vertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(m_vertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[3]);
		glBufferData(GL_ARRAY_BUFFER, directions.size() * sizeof(directions[0]), &directions[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (instance)
		{
			glDrawElementsInstanced(GL_LINE_STRIP, m_drawCount, GL_UNSIGNED_INT, NULL, instances.size());
		}
		else
		{
			glDrawElements(GL_LINE_STRIP, m_drawCount, GL_UNSIGNED_INT, NULL);
		}

		glBindVertexArray(0);

		//glLineWidth(0.1f);
		//glBegin(GL_LINE_STRIP);
		//for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		//{
		//	Particle* p = *it;

		//	if (!p->enabled)
		//	{
		//		glColor3f(1.0f, .2f, .2f);
		//	}
		//	else
		//	{
		//		glColor3f(1.0f, 1.0f, 1.0f);
		//	}

		//	glVertex3f(p->position.GetX(), p->position.GetY(), p->position.GetZ());
		//}
		//glEnd();
		//glFlush();
	}

	void FTL::Collide(SphereCollider& coll)
	{
		for each (auto p in particles)
		{
			if (!p->enabled)
			{
				continue;
			}

			Vector3 collPos =  coll.GetPosition();

			if ((p->position - collPos).magnitude() <= coll.radius)
			{
				Vector3 force = (p->position - collPos);
				force.normalize();
				force = force * (coll.radius - (p->position - collPos).magnitude());

				p->forces = force;
				/*}*/
			}
		}
	
	}

	void FTL::SetNumberOfParticles(int num)
	{
		for each(auto part in particles)
		{
			delete(part);
		}
		particles.clear();
		float mass = Random::Range(0.2f, 0.8f);
		for (int i = 0; i < num; ++i)
		{
			Particle* p = new Particle(pos, mass); //rx_random(1.0f, 10.0f));
			particles.push_back(p);
			pos = pos + originalDir;
		}
		particles[0]->enabled = false;

		m_drawCount = particles.size();

		positions.clear();
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			positions.push_back((*it)->position);
		}

		indicies.clear();
		for (GLuint i = 0; i < positions.size(); i++)
		{
			indicies.push_back(i);
		}


		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Indicies
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[4]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(indicies[0]), &indicies[0], GL_DYNAMIC_DRAW);

	}

	void FTL::SetInstances(std::vector<Vector3> instancesPos)
	{
		instances.clear();
		instances.push_back(Vector3(0, 0, 0));
		for (GLuint i = 1; i < instancesPos.size(); i++)
		{
			instances.push_back(instancesPos[i]);
		}

		//Instanced Positions
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
		glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(instances[0]), &instances[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void FTL::SetColors(Vector4 baseColor, float variation)
	{
		colors.clear();
		for (GLuint i = 0; i < instances.size(); i++)
		{
			Vector4 col = Vector4(baseColor.GetX() + Random::Range(-variation, variation),
								  baseColor.GetY() + Random::Range(-variation, variation), 
								  baseColor.GetZ() + Random::Range(-variation, variation),
								  baseColor.GetW());
			colors.push_back(col);
		}

		//Instanced Colors
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

}