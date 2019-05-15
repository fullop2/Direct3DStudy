#include "Snow.h"



Snow::Snow(CBoundingBox* boundingBox, int numParticles)
{
	mBoundingBox = *boundingBox;
	mSize = 0.8f;
	mVBSize = 2048;
	mVBOffset = 0;
	mVBBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
	{
		addParticle();
	}
}


Snow::~Snow()
{
}

void Snow::resetParticle(Attribute* attribute)
{
	attribute->_isAlive = true;

	GetRandomVector(
		&attribute->_position,
		&mBoundingBox.GetMin(),
		&mBoundingBox.GetMax());
	attribute->_position.y = mBoundingBox.GetMax().y;

	attribute->_velocity.x = GetRandomFloat(0.0f, 1.0f)*-3.0f;
	attribute->_velocity.y = GetRandomFloat(0.0f, 1.0f)*-10.0f;
	attribute->_velocity.z = 0;

	attribute->_color = WHITE;
}
void Snow::update(float timeDelta)
{
	for (auto i = mParticles.begin(); i != mParticles.end();i++)
	{
		i->_position += i->_velocity * (timeDelta * 0.01f);

		if (mBoundingBox.IsPointInside(i->_position) == false)
		{
			resetParticle(&(*i));
		}
	}
}
