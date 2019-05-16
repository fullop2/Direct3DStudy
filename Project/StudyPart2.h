#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "ObjectManager.h"

namespace Part2
{
	// D3DXCreate* 함수를 이용한 3D 오브젝트 드로잉
	void useD3DXCreate(LPDIRECT3DDEVICE9& device, ObjectManager& objectManager);

	// 버텍스, 인덱스 버퍼를 이용한 3D 오브젝트 드로잉
	void useBuffer(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// 색상을 가지고 있는 버텍스를 이용한 3D 오브젝트 드로잉
	void useVertexColor(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// 노말벡터, 재질을 가지고 있는 버텍스를 이용한 3D 오브젝트 드로잉
	void useVertexLight(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// 노말벡터, 재질, 텍스처를 가지고 있는 버텍스
	void useVertexTexture(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// 블렌딩
	void useBlending(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// 스텐실
	void useStencil(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);
}