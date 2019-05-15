#include "ParticleSystem.h"



ParticleSystem::ParticleSystem()
{
	srand(1);
}


ParticleSystem::~ParticleSystem()
{
	 SAFE_DELETE(mTex);
	 SAFE_DELETE(mVB);
}

bool ParticleSystem::init(LPDIRECT3DDEVICE9 device, char* texFileName)
{
	HRESULT hr = device->CreateVertexBuffer(
		mVBSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT,
		&mVB, 0);
	mDevice = device;

	hr = D3DXCreateTextureFromFile(
		device,
		texFileName,
		&mTex);

	return true;
}

void ParticleSystem::reset()
{
	for (auto& i : mParticles)
	{
		resetParticle(&i);
	}
}

void ParticleSystem::addParticle()
{
	Attribute attribute;
	resetParticle(&attribute);
	mParticles.push_back(attribute);
}

void ParticleSystem::preRender()
{
	mDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	mDevice->SetRenderState(D3DRS_LIGHTING, false);
	mDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	mDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	mDevice->SetRenderState(D3DRS_POINTSIZE,(DWORD) mSize);
	mDevice->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0);

	mDevice->SetRenderState(D3DRS_POINTSCALE_A, (DWORD)0);
	mDevice->SetRenderState(D3DRS_POINTSCALE_B, (DWORD)0);
	mDevice->SetRenderState(D3DRS_POINTSCALE_C, (DWORD)1);

	mDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	mDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	mDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void ParticleSystem::postRender()
{
	mDevice->SetRenderState(D3DRS_LIGHTING, true);
	mDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	mDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void ParticleSystem::removeDeadParticles()
{
	auto i = mParticles.begin();

	while (i != mParticles.end())
	{
		if (i->_isAlive)
		{
			++i;
		}
		else
		{
			i = mParticles.erase(i);
		}
	}
}

void ParticleSystem::render()
{
	if (!mParticles.empty())
	{
		preRender();

		mDevice->SetTexture(0, mTex);
		mDevice->SetFVF(Particle::FVF);
		mDevice->SetStreamSource(0, mVB, 0, sizeof(Particle));

		if (mVBOffset >= mVBSize)
			mVBOffset = 0;

		Particle* v = 0;
		mVB->Lock(
			mVBOffset * sizeof(Particle),
			mVBBatchSize * sizeof(Particle),
			(void**)&v,
			mVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
		);

		DWORD numParticlesInBatch = 0;

		for (auto i = mParticles.begin(); i != mParticles.end(); ++i)
		{
			if (i->_isAlive)
			{
				v->_position = i->_position;
				v->_color = (D3DCOLOR)i->_color;
				v++;
				numParticlesInBatch++;

				if (numParticlesInBatch == mVBBatchSize)
				{
					mVB->Unlock();

					mDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						mVBOffset,
						mVBBatchSize);

					mVBOffset += mVBBatchSize;

					if (mVBOffset >= mVBSize)
					{
						mVBOffset = 0;
					}

					mVB->Lock(
						mVBOffset * sizeof(Particle),
						mVBBatchSize * sizeof(Particle),
						(void**)&v,
						mVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				}
			}
		}
		mVB->Unlock();
		if (numParticlesInBatch)
		{
			mDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				mVBOffset,
				numParticlesInBatch);
		}

		mVBOffset += mVBBatchSize;

		postRender();
	}
}

bool ParticleSystem::isEmpty()
{
	return mParticles.empty();
}

bool ParticleSystem::isDead()
{
	std::list<Attribute>::iterator i;
	for (i = mParticles.begin(); i != mParticles.end(); i++)
	{
		if (i->_isAlive)
			return false;
	}

	return true;
}