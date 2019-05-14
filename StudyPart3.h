#pragma once

#include <fstream>

#include "stdafx.h"

class ObjectManager;
class ObjectFactory;
class Renderer;

namespace Part3
{
	void useID3DXFont(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE sprite, ObjectManager& ObjectManager, ObjectFactory* objectFactory);

	void useID3DXBaseMesh(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager, ObjectFactory* objectFactory);

	void useXFile(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager,Renderer * renderer);

	void useBoundingVolume(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager, Renderer * renderer);

	void useTerrain(LPDIRECT3DDEVICE9 device, ObjectManager& objectManager);

	void useParticle(LPDIRECT3DDEVICE9 device);
}