#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "ObjectManager.h"

namespace Part2
{
	// D3DXCreate* �Լ��� �̿��� 3D ������Ʈ �����
	void useD3DXCreate(LPDIRECT3DDEVICE9& device, ObjectManager& objectManager);

	// ���ؽ�, �ε��� ���۸� �̿��� 3D ������Ʈ �����
	void useBuffer(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// ������ ������ �ִ� ���ؽ��� �̿��� 3D ������Ʈ �����
	void useVertexColor(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// �븻����, ������ ������ �ִ� ���ؽ��� �̿��� 3D ������Ʈ �����
	void useVertexLight(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// �븻����, ����, �ؽ�ó�� ������ �ִ� ���ؽ�
	void useVertexTexture(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// ����
	void useBlending(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);

	// ���ٽ�
	void useStencil(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager);
}