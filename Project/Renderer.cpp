#include "Renderer.h"
#include "CTexture.h"
#include "C3DModel.h"

Renderer::Renderer(HWND hWnd)
{
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS pp = { 0, };

	ZeroMemory(&pp, sizeof(pp));

	pp.Windowed = true;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = hWnd;
	pp.BackBufferWidth = SCREEN_WIDTH;
	pp.BackBufferHeight = SCREEN_HEIGHT;
	pp.EnableAutoDepthStencil = true;			// Z-buffer�� �ڵ����� ����ϰ� �Ѵ�
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;		// ���� ���Ľ��� �����Ѵ�
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// ��ġ ����
	mD3D->CreateDevice(
		0,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp,
		&mDevice);

	D3DXCreateSprite(mDevice, &mSprite);
}

Renderer::~Renderer()
{
}

void Renderer::CleanD3D()
{
	SAFE_RELEASE(mDevice);
	SAFE_RELEASE(mD3D);
}

// 2d�� ���� �ؽ��� �ε�
LPDIRECT3DTEXTURE9 Renderer::LoadTexture(LPCSTR name, D3DXIMAGE_INFO *srcInfo)
{
	LPDIRECT3DTEXTURE9 value;

	// D3DX_DEFAULT_NONPOW2 - �ؽ��� �ε��� 2�� �������� �ƴ� ��쵵 ���� �� �ְ� ��
	if (FAILED(D3DXCreateTextureFromFileEx(mDevice, name, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 0, 0, srcInfo, 0, &value)))
		return nullptr;
	else	
		return value;
}

void Renderer::Load2DTexture(LPCSTR name, CTexture** ppTexture)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 tex = LoadTexture(name, &info);
	*ppTexture = new CTexture(tex, info.Height, info.Width);
}

// ���, ��ȯ �޽�, ��ȯ ����, ��ȯ �ؽ���
void Renderer::LoadXObjects(LPCSTR name, C3DModel** ppModel)
{
	ID3DXBuffer* adjBuffer = nullptr;
	ID3DXBuffer* mtrlBuffer = nullptr;
	DWORD numMtrls = 0;
	ID3DXMesh * mesh = nullptr;
	C3DModel * pModel = new C3DModel();

	HRESULT hr = D3DXLoadMeshFromX(
		name,
		D3DXMESH_MANAGED,
		mDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&mesh);

	mesh->GetAttributeTable(0, &(pModel->mNumSubsets));
	pModel->mMesh = mesh;
	pModel->mAdjacency = adjBuffer;

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* tMtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < numMtrls; ++i)
		{
			tMtrls[i].MatD3D.Ambient = tMtrls[i].MatD3D.Diffuse ;
			pModel->mMtrls->push_back(tMtrls[i].MatD3D);

			if (tMtrls[i].pTextureFilename != 0)
			{
				LPDIRECT3DTEXTURE9 tex = nullptr;
				D3DXCreateTextureFromFile(
					mDevice,
					(LPCSTR)tMtrls[i].pTextureFilename,
					&tex);
				pModel->mTextures->push_back(tex);
			}
			else
			{
				pModel->mTextures->push_back(nullptr);
			}
		}
	}

	*ppModel = pModel;
	// �ӽ� material ������
	SAFE_RELEASE(mtrlBuffer);
	return;
}