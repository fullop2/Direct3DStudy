//#include <afxwin.h>

#include "StudyPart3.h"
#include "CText.h"
#include "CTexture.h"
#include "C3DModel.h"
#include "ObjectManager.h"
#include "Object3D.h"
#include "Renderer.h"



void Part3::useID3DXFont(LPDIRECT3DDEVICE9 device,LPD3DXSPRITE sprite, ObjectManager& ObjectManager)
{
	//////////////////////////////////////////////////////////////////
	////// old type //////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	//text를 이루는 속성을 채움
	LOGFONT logFont;
	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = 100; // 논리적 단위
	logFont.lfWidth = 50; // 논리적 단위
	logFont.lfWeight = 500; // 굵기의 단위
	logFont.lfItalic = false;
	logFont.lfCharSet = DEFAULT_CHARSET;
	strcpy(logFont.lfFaceName, "CF Glitch City"); // 글꼴 스타일

	HFONT hFont = CreateFontIndirect(&logFont);
	
	////////////////////////////////////////////////////////
	///// new type /////////////////////////////////////////
	////////////////////////////////////////////////////////
	/*
	LPD3DXFONT font = nullptr;
	
	AddFontResourceEx("./Fonts/CFGlitchCity.ttf", FR_PRIVATE, NULL);
	D3DXCreateFont(
		device,								// pDevice
		100,								// Height
		0,									// Width (0으로 설정)
		FW_THIN,							// Weight
		1,									// Mip Level
		false ,								// Italic
		DEFAULT_CHARSET,					// Charset
		OUT_DEFAULT_PRECIS,					// Precision
		DEFAULT_QUALITY,					// Quality
		DEFAULT_PITCH | FF_DONTCARE,		// Pitch And Family
		"CF Glitch City",					// Face Name
		&font);								// ppFont

	CText * text = new CText(font,0xfff0f0f0, "HELLO DIRECT X");
	ObjectManager.AddText(text);
	text->Move(100, 100);
	//font->DrawText(sprite, "Hello World", -1, DT_TOP | DT_LEFT, DT_CALCRECT, 0xff000000);
	*/

	////////////////////////////////////////////////////////////////////////////////////////////
	//////////// D3DXCREATETEXT ////////////////////////////////////////////
	//////////////////////////////////////////////////////////////

	HDC hdc = CreateCompatibleDC(0);


	LPD3DXMESH txtMesh;

	HFONT hFontOld;

	hFontOld = (HFONT)SelectObject(hdc, hFont);

	HRESULT rt = D3DXCreateText(device, hdc, "HELLO DIRECT X", 0.001f, 0.4f, &txtMesh, 0, 0);

	D3DMATERIAL9 * txtMtrl = new D3DMATERIAL9{};
	txtMtrl->Ambient = WHITE * 0.7f;
	txtMtrl->Diffuse = WHITE;
	txtMtrl->Specular = WHITE;
	txtMtrl->Emissive = BLACK;
	txtMtrl->Power = 1.0f;

	ObjectBuffer * txt = new ObjectBuffer(txtMesh,txtMtrl,nullptr);
	ObjectManager.Add(txt);
	txt->Move(10, 15,-10);

	SelectObject(hdc, hFontOld);
	//DelectObject(hFont);
	DeleteDC(hdc);
}


// declare
void dumpVertices(std::ofstream& outFile, LPD3DXMESH mesh);
void dumpIndices(std::ofstream& outFile, LPD3DXMESH mesh);
void dumpAttributeTable(std::ofstream& outFile, LPD3DXMESH mesh);
void dumpAttributeBuffer(std::ofstream& outFile, LPD3DXMESH mesh);
void dumpAdjacencyBuffer(std::ofstream& outFile, LPD3DXMESH mesh);

void Part3::useID3DXBaseMesh(LPDIRECT3DDEVICE9 device, ObjectManager& ObjectManager)
{
	// 0. 메쉬 생성
	LPD3DXMESH mesh = nullptr;
	const DWORD  numSubsets = 3;

	TexVec * texture = new TexVec(3);
	MtrlVec * mtrl = new MtrlVec;


	std::ofstream OutFile;

	HRESULT hr = D3DXCreateMeshFVF(
		12,
		24,
		D3DXMESH_MANAGED,
		TVertex::FVF,
		device,
		&mesh);

	// 1. 버텍스 버퍼 채우기
	TVertex* v = nullptr;
	mesh->LockVertexBuffer(0, (void**)&v);

	// fill in the front face vertex data
	v[0] = TVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[1] = TVertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 5.0f);
	v[2] = TVertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 5.0f, 5.0f);
	v[3] = TVertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

	// fill in the back face vertex data
	v[4] = TVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[5] = TVertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f);
	v[6] = TVertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 5.0f, 5.0f);
	v[7] = TVertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 5.0f, 0.0f);

	// fill in the top face vertex data
	v[8] = TVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[9] = TVertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f);
	v[10] = TVertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 5.0f, 5.0f);
	v[11] = TVertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.0f);

	// fill in the bottom face vertex data
	v[12] = TVertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[13] = TVertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 5.0f);
	v[14] = TVertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 5.0f, 5.0f);
	v[15] = TVertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 5.0f, 0.0f);

	// fill in the left face vertex data
	v[16] = TVertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[17] = TVertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 5.0f);
	v[18] = TVertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 5.0f, 5.0f);
	v[19] = TVertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 5.0f, 0.0f);

	// fill in the right face vertex data
	v[20] = TVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[21] = TVertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 5.0f);
	v[22] = TVertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 5.0f, 5.0f);
	v[23] = TVertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 5.0f, 0.0f);

	mesh->UnlockVertexBuffer();

	// 2. 인덱스 버퍼 채우기
	WORD* i = nullptr;
	mesh->LockIndexBuffer(0, (void**)&i);

	// fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	mesh->UnlockIndexBuffer();

	// 3. 속성 버퍼 채우기
	DWORD* attributeBuffer = nullptr;
	mesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int a = 0; a < 4; ++a)
		attributeBuffer[a] = 1;	// subset 0
	for (int b = 4; b < 8; ++b)
		attributeBuffer[b] = 0; // subset 1
	for (int c = 8; c < 12; ++c)
		attributeBuffer[c] = 2;	// subset 2

	mesh->UnlockAttributeBuffer();

	// 4. 최적화
	vector<DWORD> adjacencyBuffer(mesh->GetNumFaces() * 3);
	mesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	hr = 1;
	hr = mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0);

	OutFile.open("Mesh Dump.txt");

	dumpVertices(OutFile, mesh);
	dumpIndices(OutFile, mesh);
	dumpAttributeTable(OutFile, mesh);
	dumpAttributeBuffer(OutFile, mesh);
	dumpAdjacencyBuffer(OutFile, mesh);


	OutFile.close();
	
	hr = D3DXCreateTextureFromFile(
		device,
		"./Resource/brick0.jpg",
		&(*texture)[0]);

	hr = D3DXCreateTextureFromFile(
		device,
		"./Resource/brick1.jpg",
		&(*texture)[1]);

	hr = D3DXCreateTextureFromFile(
		device,
		"./Resource/checker.jpg",
		&(*texture)[2]);
	
	for(int a = 0; a < 3; ++a)
	mtrl->push_back(D3DMATERIAL9(WHITE_MTRL));

	C3DModel *block = new C3DModel{ mesh,mtrl,texture };

	Object3D* oBlock = new Object3D();
	oBlock->Init(block);
	ObjectManager.Add(oBlock);
	oBlock->SetScale(D3DXVECTOR3{ 5,5,5 });

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

}

// define
void dumpVertices(std::ofstream& outFile, LPD3DXMESH mesh)
{
	outFile << "Vertices:" << std::endl;
	outFile << "---------" << std::endl << std::endl;

	TVertex* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);
	for (size_t i = 0; i < mesh->GetNumVertices(); i++)
	{
		outFile << "Vertex " << i << ": (";
		outFile << v[i]._x << ", " << v[i]._y << ", " << v[i]._z << ", ";
		outFile << v[i]._nx << ", " << v[i]._ny << ", " << v[i]._nz << ", ";
		outFile << v[i]._u << ", " << v[i]._v << ")" << std::endl;
	}
	mesh->UnlockVertexBuffer();

	outFile << std::endl << std::endl;
}
void dumpIndices(std::ofstream& outFile, LPD3DXMESH mesh)
{
	outFile << "Indices:" << std::endl;
	outFile << "--------" << std::endl << std::endl;

	WORD* indices = 0;
	mesh->LockIndexBuffer(0, (void**)&indices);

	for (size_t i = 0; i < mesh->GetNumFaces(); i++)
	{
		outFile << "Triangle " << i << ": ";
		outFile << indices[i * 3] << " ";
		outFile << indices[i * 3 + 1] << " ";
		outFile << indices[i * 3 + 2] << std::endl;
	}
	mesh->UnlockIndexBuffer();

	outFile << std::endl << std::endl;
}
void dumpAttributeTable(std::ofstream& outFile, LPD3DXMESH mesh)
{
	outFile << "Attribute Table:" << std::endl;
	outFile << "----------------" << std::endl << std::endl;

	// number of entries in the attribute table
	DWORD numEntries = 0;

	mesh->GetAttributeTable(0, &numEntries);

	vector<D3DXATTRIBUTERANGE> table(numEntries);

	mesh->GetAttributeTable(&table[0], &numEntries);

	for (size_t i = 0; i < numEntries; i++)
	{
		outFile << "Entry " << i << std::endl;
		outFile << "-----------" << std::endl;

		outFile << "Subset ID:    " << table[i].AttribId << std::endl;
		outFile << "Face Start:   " << table[i].FaceStart << std::endl;
		outFile << "Face Count:   " << table[i].FaceCount << std::endl;
		outFile << "Vertex Start: " << table[i].VertexStart << std::endl;
		outFile << "Vertex Count: " << table[i].VertexCount << std::endl;
		outFile << std::endl;
	}

	outFile << std::endl << std::endl;
}
void dumpAttributeBuffer(std::ofstream& outFile, LPD3DXMESH mesh)
{
	outFile << "Attribute Buffer:" << std::endl;
	outFile << "-----------------" << std::endl << std::endl;

	// 읽기 전용으로 안열면 D3DXATTRIBUTERANGE가 날라감..
	DWORD* attributeBuffer = 0;
	mesh->LockAttributeBuffer(D3DLOCK_READONLY, &attributeBuffer);	

	// an attribute for each face
	for (size_t i = 0; i < mesh->GetNumFaces(); i++)
	{
		outFile << "Triangle lives in subset " << i << ": ";
		outFile << attributeBuffer[i] << std::endl;
	}
	mesh->UnlockAttributeBuffer();

	outFile << std::endl << std::endl;
}
void dumpAdjacencyBuffer(std::ofstream& outFile, LPD3DXMESH mesh)
{
	outFile << "Adjacency Buffer:" << std::endl;
	outFile << "-----------------" << std::endl << std::endl;

	// three enttries per face
	vector<DWORD> adjacencyBuffer(mesh->GetNumFaces() * 3);

	mesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	for (size_t i = 0; i < mesh->GetNumFaces(); i++)
	{
		outFile << "Triangle's adjacent to triangle " << i << ": ";
		outFile << adjacencyBuffer[i * 3] << " ";
		outFile << adjacencyBuffer[i * 3 + 1] << " ";
		outFile << adjacencyBuffer[i * 3 + 2] << std::endl;
	}

	outFile << std::endl << std::endl;
}
