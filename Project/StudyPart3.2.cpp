#include "StudyPart3.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "CBound.h"
#include "Object3D.h"

void Part3::useXFile(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager, Renderer * renderer)
{
	//////////////////////////////////////////////////////////////////////
	ID3DXBuffer * ib = nullptr;

	// 빈 ID3DXBuffer를 만드는 함수
	D3DXCreateBuffer(
		4 * sizeof(int),			/* 버퍼의 크기(바이트 단위)*/
		&ib /* 생성된 버퍼를 리턴*/);

	void * point = ib->GetBufferPointer(); // 데이터 시작을 가리키는 포인터를 리턴
	DWORD  size = ib->GetBufferSize();	// 버퍼 크기를 바이트 수로 리턴

	SAFE_RELEASE(ib);


	////////////////////////////////////////////////////////////////////////


	Object3D * ship = new Object3D();
	C3DModel * ship3d = nullptr;
	renderer->LoadXObjects("media/bigship1.x", &ship3d);
	ship->Init(ship3d);

	ship->Move(1, 0, 0);
	ship->SetTag(string("Base"));

	ID3DXMesh * shipMesh = nullptr;
	ship3d->GetMesh(&shipMesh);

	// 메쉬에 법선 정보가 없는 경우 추가하는 코드
	if (!(shipMesh->GetFVF() & D3DFVF_NORMAL)) // NORMAL 성분이 없는 경우
	{
		ID3DXMesh * pTmpMesh = nullptr;
		shipMesh->CloneMeshFVF(D3DXMESH_MANAGED, shipMesh->GetFVF() | D3DFVF_NORMAL, device, &pTmpMesh);
		D3DXComputeNormals(shipMesh, 0);
		SAFE_RELEASE(shipMesh);
		shipMesh = pTmpMesh;
	}
	
	// 프로그레시브 메쉬
	ID3DXPMesh * pMesh = nullptr;
	ID3DXBuffer * adjacency = nullptr;
	ship3d->GetAdjacency(&adjacency);

	D3DXGeneratePMesh(
		shipMesh,	// 원본 메쉬
		(DWORD*)adjacency->GetBufferPointer(),
		0, 0, 1, D3DXMESHSIMP_FACE,
		&pMesh);

	DWORD numSubset;
	pMesh->GetAttributeTable(0, &numSubset);
	
	MtrlVec * mtrl = new MtrlVec;
	TexVec *tex = new TexVec;

	for (DWORD i = 0; i < numSubset; ++i)
	{
		mtrl->push_back(D3DMATERIAL9{ YELLOW_MTRL });
		tex->push_back(nullptr);
	}
	RSVec * A = new RSVec;
	A->push_back(std::make_pair(D3DRS_FILLMODE, D3DFILL_WIREFRAME));

	pMesh->SetNumFaces(8);
	C3DModel * ship22 = new C3DModel(pMesh,mtrl,tex,nullptr,A);

	Object3D * ship2 = new Object3D();
	ship2->Init(ship22);
	ship2->SetTag(string("Progressive"));
	ship2->Move(1, 0, 0);
	ObjectManager.Add(ship2);
	ObjectManager.Add(ship);
}

void Part3::useBoundingVolume(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager, Renderer * renderer)
{
	/* 
	Bounding Volume - 경계 볼륨
	가시성 테스트와 충돌 테스트를 위한 가상의 경계
	가시성 테스트의 경우 경계 볼륨이 보이지 않는다면 물체도 보이지 않는다고 할 수 있다.
	충돌 테스트의 경우 경계 볼륨 외부의 오브젝트에 대해 충돌 판정을 검사할 필요가 없다.
	*/

	Object3D * ship = new Object3D();
	C3DModel * shipModel = nullptr;
	renderer->LoadXObjects("media/bigship1.x", &shipModel);
	ship->Init(shipModel);

	ship->Move(1, 0, 0);
	ship->SetTag(string("Base"));
	ObjectManager.Add(ship);

	/*
	CBoundingSphere * cBoundingSphere = nullptr;
	ComputeBoundingSphere(shipModel, &cBoundingSphere);

	ID3DXMesh* sphereMesh = nullptr;

	D3DXCreateSphere(device, 10.0f, 20, 20, &sphereMesh, 0);

 	C3DModel * sphere = new C3DModel(sphereMesh);
	Object3D * shipB = new Object3D;
	shipB->Init(sphere);

	ObjectManager.Add(shipB);
	
	SAFE_DELETE(cBoundingSphere);
	*/
}

void Part3::useTerrain(LPDIRECT3DDEVICE9 device, ObjectManager& objectManager, CTerrain** ppTerrain)
{
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);
	*ppTerrain = new CTerrain(device, "./Resource/castlehm257.raw", 257, 257, 1, 0.2f);
	(*ppTerrain)->GenTexture(&lightDirection);

}