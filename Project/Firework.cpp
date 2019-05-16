#include "Firework.h"


Firework::Firework(D3DXVECTOR3* origin, int numParticles)
{
	_origin = *origin;
	mSize = 0.8f;
	mVBSize = 2048;
	mVBOffset = 0;
	mVBBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
	{
		addParticle();
	}
}
void Firework::resetParticle(Attribute* attribute)
{
	attribute->_isAlive = true;
	attribute->_position = _origin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	GetRandomVector(
		&attribute->_velocity,
		&min,
		&max);

	D3DXVec3Normalize(&attribute->_velocity, &attribute->_velocity);

	attribute->_color = D3DXCOLOR(
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->_age = 0.0f;
	attribute->_lifeTime = 20.0f;
}
void Firework::update(float timeDelta)
{
	for (auto i = mParticles.begin(); i != mParticles.end(); i++)
	{
		if (i->_isAlive)
		{
			i->_position += i->_velocity * timeDelta * 0.01f;
			i->_age += (timeDelta * .001f);
			if (i->_age > i->_lifeTime)
				i->_isAlive = false;
		}
	}
}
void Firework::preRender()
{
	ParticleSystem::preRender();

	mDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	mDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}
void Firework::postRender()
{
	ParticleSystem::postRender();

	mDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}