#include "Stage_Main.h"

#include "FlexCamera.h"
#include "Light.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

// D3D9 서적 예제 함수들 구현한 것
#include "StudyPart2.h"
#include "StudyPart3.h"

Stage_Main::Stage_Main(Renderer* renderer)
	:Scene(renderer)
{
	mSkyColor = D3DCOLOR_XRGB(0,0,0);
}

Stage_Main::~Stage_Main()
{
}

bool Stage_Main::Init()
{
	// 조명 및 카메라만 설정한다
	// 이외의 코드는 다른 함수로 빼내서 사용한다

	// add lights
	mDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	mDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	Light* light = new Light;
	D3DXVECTOR3 di = D3DXVECTOR3{ 1.0f,-1.0f,0.0f };
	D3DXCOLOR color = WHITE;

	light->Init(D3DLIGHT_DIRECTIONAL, &color, &di, 0);
	mDevice->SetLight(0, light->GetLight());
	mDevice->LightEnable(0, true);
	mObjectManager.Add(light);
	
	// set render state
	mDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	mDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	mDevice->SetRenderState(D3DRS_LIGHTING,	true);
	
	mCamera = new FlexCamera{mDevice};
	mObjectManager.Add(mCamera);

	ObjectFactory *objectFactory = new ObjectFactory(mDevice);
	Part3::useTerrain(mDevice, mObjectManager);
	Part3::useID3DXBaseMesh(mDevice, mObjectManager, objectFactory);
	delete objectFactory;
	return true;
}