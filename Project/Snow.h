#pragma once
#include "ParticleSystem.h"
class Snow :
	public ParticleSystem
{
public:
	Snow(CBoundingBox* boundingBox, int numParticles);
	virtual ~Snow();
	
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};

