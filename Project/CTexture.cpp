#include "CTexture.h"

CTexture::~CTexture()
{
	SAFE_RELEASE(mTexture);
}