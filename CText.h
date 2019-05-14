#pragma once
#include "Renderer.h"
#include "Object2D.h"

class CText
	:public Object2D
{
public:
	void Draw(ID3DXSprite* sprite) override;
	int Update() override;
	int Destroy() override;

	CText(LPD3DXFONT font, D3DXCOLOR color, LPCSTR text = "text");
	~CText();
private:
	RECT screen;
	LPD3DXFONT mFont;
	D3DXCOLOR mColor;
	LPCSTR mText;
};

