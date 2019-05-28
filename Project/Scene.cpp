#include "Renderer.h"
#include "Window.h"

#include "Scene.h"
#include "Physics2D.h"

#include "ParticleSystem.h"
#include "CTerrain.h"
#include "CText.h"
#include "Light.h"
#include "Camera.h"
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

Scene::~Scene()
{
	SAFE_DELETE(mCamera);
	SAFE_DELETE(mTerrain);
	for(auto* psys : mParticleSystem)
		SAFE_DELETE(psys);
	for (auto* txt : mText)
		SAFE_DELETE(txt);
	for (auto* lgt : mLight)
		SAFE_DELETE(lgt);

}

void Scene::Update(float deltaTime)
{
	mCamera->Update();
	mObjectManager.Update(deltaTime);
	Physics2D::Get()->Update();

	for(auto psys : mParticleSystem)
		psys->update(deltaTime);
	for (auto txt : mText)
		txt->Update();
}

void Scene::Draw()
{
	mDevice->BeginScene();
	mDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, mSkyColor, 1, 0);		// �⺻ ȭ�� �����, Z-buffer �����, ���ٽ� �����

	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//mDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	mObjectManager.Draw(mDevice);

	for (auto txt : mText)
		txt->Draw(mSprite);

	mTerrain->Draw(mDevice);

	for (auto psys : mParticleSystem)
		psys->render();

	mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	mSprite->Begin(D3DXSPRITE_ALPHABLEND);

	mObjectManager.Draw2D(mSprite);

	mSprite->End();

	mDevice->EndScene();
	mDevice->Present(0, 0, 0, 0);
}

void Scene::Destroy()
{
}