#include "Camera.h"
#include "Renderer.h"
#include "Window.h"

#include "Scene.h"
#include "Physics2D.h"
#include "ParticleSystem.h"
//
// DirectX 9���� ȭ�鿡 ������Ʈ�� ������
// 3D�� ��� mesh, texture, material, ��ǥ ���� ������ device�� �Ѱ��ְ�
// mesh���� �׸��� �ؾ��Ѵ�
//
// 2D�� ��� texture, ��ǥ ���� ������ �Ѱ��ְ�
// sprite�� �׸���(Draw) �ؾ��Ѵ�
//

Scene::Scene(Renderer* renderer)
	:mDevice(renderer->GetDevice()), mSprite(renderer->GetSprite())
{
	this->mRenderer = renderer;
	mCamera = nullptr;
	mSkyColor = D3DCOLOR_XRGB(255, 155, 255);

}

void Scene::Update(float timeDelta)
{
	mCamera->Update();
	mObjectManager.Update();
	Physics2D::Get()->Update();
	mParticleSystem->update(timeDelta);
}

void Scene::Draw()
{
	mDevice->BeginScene();
	mDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, mSkyColor, 1, 0);		// �⺻ ȭ�� �����, Z-buffer �����, ���ٽ� �����
		// 3d ������Ʈ �����
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	mDevice->SetTransform(D3DTS_WORLD, &I);
	mParticleSystem->render();
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//mDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	mObjectManager.Draw(mDevice);

	mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	mSprite->Begin(D3DXSPRITE_ALPHABLEND);

	mObjectManager.Draw2D(mSprite);

	mSprite->End();

	mDevice->EndScene();
	mDevice->Present(0, 0, 0, 0);
}

void Scene::Destroy()
{
	delete mCamera;
	delete mParticleSystem;
}