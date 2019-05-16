#pragma once
#include "Renderer.h"
#include "stdafx.h"

class CText
{
public:
	void Draw(ID3DXSprite* sprite);
	int Update();
	int Destroy();

	CText(LPD3DXFONT font, D3DXCOLOR color, LPCSTR text = "text");
	~CText();
private:
	RECT screen;
	LPD3DXFONT mFont;
	D3DXCOLOR mColor;
	LPCSTR mText;
	D3DXVECTOR3 mPosition;
};

