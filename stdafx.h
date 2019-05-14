#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#define map std::unordered_map
#define vector std::vector
#define pair std::pair
typedef std::string string;

#define MtrlVec vector<D3DMATERIAL9>
#define TexVec vector<IDirect3DTexture9*>
#define RSVec vector< pair < D3DRENDERSTATETYPE, DWORD> >

#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p) = nullptr;}}
#define SAFE_DELETE(p) {if(p){delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p){if(p){delete[] (p); (p) = nullptr;}}



 
D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
bool Equals(float lhs, float rhs);
 

namespace
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//
	// Colors
	//
	const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	const D3DXCOLOR BEACH_SAND(D3DCOLOR_XRGB(255, 249, 157));
	const D3DXCOLOR DESERT_SAND(D3DCOLOR_XRGB(250, 205, 135));

	const D3DXCOLOR LIGHTGREEN(D3DCOLOR_XRGB(60, 184, 120));
	const D3DXCOLOR  PUREGREEN(D3DCOLOR_XRGB(0, 166, 81));
	const D3DXCOLOR  DARKGREEN(D3DCOLOR_XRGB(0, 114, 54));

	const D3DXCOLOR LIGHT_YELLOW_GREEN(D3DCOLOR_XRGB(124, 197, 118));
	const D3DXCOLOR  PURE_YELLOW_GREEN(D3DCOLOR_XRGB(57, 181, 74));
	const D3DXCOLOR  DARK_YELLOW_GREEN(D3DCOLOR_XRGB(25, 123, 48));

	const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
	const D3DXCOLOR DARKBROWN(D3DCOLOR_XRGB(115, 100, 87));

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

	const float EPSILON = 0.001f;
} 