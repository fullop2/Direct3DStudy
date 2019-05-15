#include "Object2D.h"
#include "CTexture.h"


Object2D::Object2D()
{
	Move(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mTexture.reset(nullptr);
}


Object2D::~Object2D()
{
	Destroy();
}

bool Object2D::Init(CTexture* pTexture)
{
	if (mTexture.get())
	{
		return true;
	}
	else if (pTexture)
	{
		mTexture.reset(pTexture);
	}
	else
	{
		return false;
	}
	return true;
}


void Object2D::Draw(ID3DXSprite* sprite)
{
	IDirect3DTexture9* texture = nullptr;
	mTexture->GetTexture(&texture);
	sprite->Draw(
		texture, 
		0,
		&D3DXVECTOR3(mTexture->GetWidth()/2.0f,mTexture->GetHeight()/2.0f,0), 
		&D3DXVECTOR3(0,0,0),
		mColor);
};

int Object2D::Destroy()
{
	return true;
}