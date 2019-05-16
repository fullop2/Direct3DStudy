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

	// �� ID3DXBuffer�� ����� �Լ�
	D3DXCreateBuffer(
		4 * sizeof(int),			/* ������ ũ��(����Ʈ ����)*/
		&ib /* ������ ���۸� ����*/);

	void * point = ib->GetBufferPointer(); // ������ ������ ����Ű�� �����͸� ����
	DWORD  size = ib->GetBufferSize();	// ���� ũ�⸦ ����Ʈ ���� ����

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

	// �޽��� ���� ������ ���� ��� �߰��ϴ� �ڵ�
	if (!(shipMesh->GetFVF() & D3DFVF_NORMAL)) // NORMAL ������ ���� ���
	{
		ID3DXMesh * pTmpMesh = nullptr;
		shipMesh->CloneMeshFVF(D3DXMESH_MANAGED, shipMesh->GetFVF() | D3DFVF_NORMAL, device, &pTmpMesh);
		D3DXComputeNormals(shipMesh, 0);
		SAFE_RELEASE(shipMesh);
		shipMesh = pTmpMesh;
	}
	
	// ���α׷��ú� �޽�
	ID3DXPMesh * pMesh = nullptr;
	ID3DXBuffer * adjacency = nullptr;
	ship3d->GetAdjacency(&adjacency);

	D3DXGeneratePMesh(
		shipMesh,	// ���� �޽�
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
	Bounding Volume - ��� ����
	���ü� �׽�Ʈ�� �浹 �׽�Ʈ�� ���� ������ ���
	���ü� �׽�Ʈ�� ��� ��� ������ ������ �ʴ´ٸ� ��ü�� ������ �ʴ´ٰ� �� �� �ִ�.
	�浹 �׽�Ʈ�� ��� ��� ���� �ܺ��� ������Ʈ�� ���� �浹 ������ �˻��� �ʿ䰡 ����.
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