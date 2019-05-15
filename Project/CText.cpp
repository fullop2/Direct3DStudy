#include "CText.h"



void CText::Draw(ID3DXSprite* sprite)
{
	mFont->DrawText(sprite, mText, -1, &screen, DT_NOCLIP, mColor);
}

int CText::Update()
{

		screen.left = screen.top = 0;

	/*
	static float cnt = 0;
	const char * tmp = std::to_string(++cnt).c_str();
	*/

	return true;
}

int CText::Destroy()
{
	return true;
}


CText::CText(LPD3DXFONT font,D3DXCOLOR color , LPCSTR text)
	:mFont(font),mColor(color)
{
	mPosition.x = 0;
	mPosition.y = 0;

	mText = text;
	screen = RECT{ 0, 0, 0, 0 };
}


CText::~CText()
{
	SAFE_RELEASE(mFont);
}
