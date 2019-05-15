#include "Camera.h"
#include "Renderer.h"
#include "Window.h"

#include "Scene.h"
#include "Physics2D.h"
#include "ParticleSystem.h"
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
	mDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, mSkyColor, 1, 0);		// 기본 화면 지우기, Z-buffer 지우기, 스텐실 지우기
		// 3d 오브젝트 드로잉
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