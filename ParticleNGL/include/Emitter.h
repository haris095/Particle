#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include "Particle.h"
#include <ngl/AbstractVAO.h>
#include <memory>
class Emitter
{
public :
	Emitter(size_t _numParticles, ngl::Vec3 _pos,ngl::Vec3 _emitDir, float _spread=4.5f /* =ngl::Vec3(0.0f,-10.0f,-15.0f)*/);
	~Emitter() = default;
	void update(float _deltaT);
	void draw() const;
	void resetParticles();

private :
	void resetParticle(Particle& io_p);
	ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
	std::vector<Particle> m_particles;
	ngl::Vec3 m_pos;
	float m_spread = 4.5f;
	ngl::Vec3 m_emitDir=ngl::Vec3(0.0f,1.0f,0.0f);
	size_t m_numParticles = 1000;
	std::unique_ptr<ngl::AbstractVAO> m_vao;
	
};

#endif
