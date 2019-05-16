#pragma once

#include <fstream>

#include "stdafx.h"

class ObjectManager;
class Renderer;
class CTerrain;

namespace Part3
{
	void useID3DXFont(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE sprite, ObjectManager& ObjectManager);

	void useID3DXBaseMesh(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager);

	void useXFile(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager,Renderer * renderer);

	void useBoundingVolume(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager, Renderer * renderer);

	void useTerrain(LPDIRECT3DDEVICE9 device, ObjectManager& objectManager, CTerrain** ppTerrain);

	void useParticle(LPDIRECT3DDEVICE9 device);
}