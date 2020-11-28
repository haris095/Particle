
#include "Emitter.h"
#include <iostream>
#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>


Emitter::Emitter(size_t _numParticles, ngl::Vec3 _pos,ngl::Vec3 _emitDir , float _spread)
{
	m_pos = _pos;
	m_spread = _spread;
	m_emitDir = _emitDir;
	m_numParticles = _numParticles;
	m_particles.resize(_numParticles);
	for (auto& p : m_particles)
	{
		resetParticle(p);
	}
	

	m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

void Emitter::resetParticles()
{
	m_particles.resize(m_numParticles);
	for (auto& p : m_particles)
	{
		resetParticle(p);
	}
}


void Emitter::resetParticle(Particle& io_p)
{

	io_p.pos = m_pos;
	io_p.dir = m_emitDir * ngl::Random::randomPositiveNumber(1.0f) +  randomVectorOnSphere() *  m_spread;
	//io_p.dir.m_y = std::abs(io_p.dir.m_y);
	io_p.colour = ngl::Random::getRandomColour3();
	io_p.maxLife = static_cast<int>(ngl::Random::randomPositiveNumber(200));
	io_p.life = 0;
}
void Emitter::update(float _deltaT)
{
	
	ngl::Vec3 gravity(0.0f, -1.81f, 20.0f);
	
		for (auto& p : m_particles)
		{
			
			p.dir += gravity * _deltaT*   0.5f;
			p.pos +=  p.dir * _deltaT;
			if (++p.life >= p.maxLife || (p.pos.m_y <= -1.0f || p.pos.m_y >= 1.0f) || (p.pos.m_x <= -1.0f || p.pos.m_x >= 1.0f) || (p.pos.m_z <= -1.0f || p.pos.m_z >= 1.0f))
			{
				resetParticle(p);
			}
		
	
	}
}
void Emitter::draw() const
{
//	std::cout<<"drawing \n";
	//glPointSize(4.0);
	m_vao->bind();
	m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].pos.m_x));
	m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
	m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);

	m_vao->setNumIndices(m_particles.size());
	m_vao->draw();
	m_vao->unbind();


}

ngl::Vec3 Emitter::randomVectorOnSphere(float _radius )
{
	
	float phi = ngl::Random::randomPositiveNumber(static_cast<float>(M_PI * 2.0f));
	float costheta = ngl::Random::randomNumber();
	float u = ngl::Random::randomPositiveNumber();
	float theta = acos(costheta);
	float r = _radius * std::cbrt(u);
	return ngl::Vec3(r * sin(theta) * cos(phi),
									 r * sin(theta) * sin(phi),
									 r * cos(theta)
									);
}






