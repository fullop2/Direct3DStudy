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
// DirectX 9에서 화면에 오브젝트를 띄우려면
// 3D의 경우 mesh, texture, material, 좌표 등의 정보를 device에 넘겨주고
// mesh에서 그리게 해야한다
//
// 2D의 경우 texture, 좌표 등의 정보를 넘겨주고
// sprite가 그리게(Draw) 해야한다
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
	mDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, mSkyColor, 1, 0);		// 기본 화면 지우기, Z-buffer 지우기, 스텐실 지우기

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