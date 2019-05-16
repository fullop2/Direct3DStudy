#include "Stage_Main.h"

#include "FlexCamera.h"
#include "Light.h"
#include "ObjectManager.h"

#include "Firework.h"
#include "Snow.h"
#include "CBound.h"

#include "Player.h"

// D3D9 서적 예제 함수들 구현한 것
#include "StudyPart2.h"
#include "StudyPart3.h"

Stage_Main::Stage_Main(Renderer* renderer)
	:Scene(renderer)
{
	mSkyColor = D3DCOLOR_XRGB(30,30,100);
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

	CBoundingBox c = CBoundingBox(D3DXVECTOR3(-100, -100, -100), D3DXVECTOR3(100, 100, 100));
	D3DXVECTOR3 o = D3DXVECTOR3(0, 200, 0);
	ParticleSystem* ps =  new Snow(&c,20000);
	ps->init(mDevice, "./Resource/snowflake.dds");
	mParticleSystem.push_back(ps);

	Light* light = new Light;
	D3DXVECTOR3 di = D3DXVECTOR3{ 1.0f,-1.0f,0.0f };
	D3DXCOLOR color = WHITE;

	light->Init(D3DLIGHT_DIRECTIONAL, &color, &di, 0);
	mDevice->SetLight(0, light->GetLight());
	mDevice->LightEnable(0, true);
	mLight.push_back(light);
	
	// set render state
	mDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	mDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	mDevice->SetRenderState(D3DRS_LIGHTING,	true);
	
	mCamera = new FlexCamera{mDevice};

	Part3::useTerrain(mDevice, mObjectManager,&mTerrain);
	//Part3::useID3DXBaseMesh(mDevice, mObjectManager, objectFactory);
	
	return true;
}