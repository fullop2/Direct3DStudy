#pragma once
#include "ParticleSystem.h"
class Firework :
	public ParticleSystem
{
public:
	Firework(D3DXVECTOR3* origin, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
	void preRender();
	void postRender();
	
private:
	D3DXVECTOR3 _origin;
};

