#pragma once
#include "StudyPart2.h"
#include "MirrorStencil.h"
#include "C3DModel.h"
#include "Object3D.h"

void Part2::useBlending(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager)
{
	// teapot
	LPD3DXMESH mesh = nullptr;
	D3DMATERIAL9 teapotmtrl = RED_MTRL;
	teapotmtrl.Diffuse.a = 0.5f;

	D3DXCreateTeapot(device, &mesh, 0);
	MtrlVec * mtrls = new MtrlVec;
	mtrls->push_back(teapotmtrl);
	TexVec*  tex = new TexVec;
	tex->push_back(nullptr);
	C3DModel * model = new C3DModel(mesh, mtrls, tex);

	Object3D * tpot = new Object3D();
	tpot->Init(model);
	tpot->Move(0, 0, -3);
	ObjectManager.Add(tpot);

	// box

	LPDIRECT3DVERTEXBUFFER9 box = nullptr;

	LPDIRECT3DTEXTURE9 texture = nullptr;
	D3DXCreateTextureFromFile(device, "media/crate.jpg", &texture);

	LPDIRECT3DVERTEXBUFFER9 vb = nullptr;

	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		D3DUSAGE_WRITEONLY,
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	TVertex * v = nullptr;

	vb->Lock(0, 0, (void**)&v, 0);

	v[0] = TVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = TVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = TVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = TVertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	vb->Unlock();

	D3DMATERIAL9 * boxmtrl = new D3DMATERIAL9(WHITE_MTRL);

	ObjectBuffer * boxbuffer = new ObjectBuffer(vb, nullptr, TVertex::FVF, sizeof(TVertex), boxmtrl, texture);
	boxbuffer->Move(0, 0, 0);
	ObjectManager.Add(boxbuffer);


	//
	// Set alpha blending states.
	//

	// use alpha in material's diffuse component for alpha
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// set blending factors so that alpha component determines transparency
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void Part2::useStencil(LPDIRECT3DDEVICE9& device, ObjectManager& ObjectManager)
{
	//
	// Load Textures, set filters.
	//
	LPDIRECT3DTEXTURE9 FloorTex;
	LPDIRECT3DTEXTURE9 WallTex;
	LPDIRECT3DTEXTURE9 MirrorTex;

	D3DXCreateTextureFromFile(device, "media/checker.jpg", &FloorTex);
	D3DXCreateTextureFromFile(device, "media/brick0.jpg", &WallTex);
	D3DXCreateTextureFromFile(device, "media/ice.bmp", &MirrorTex);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//
	// add teapot
	//
	LPD3DXMESH mesh = nullptr;
	D3DMATERIAL9 teapotmtrl = RED_MTRL;
	teapotmtrl.Diffuse.a = 0.5f;

	D3DXCreateTeapot(device, &mesh, 0);
	MtrlVec * mtrls = new MtrlVec;
	mtrls->push_back(teapotmtrl);
	TexVec* tex = new TexVec;
	tex->push_back(nullptr);
	C3DModel * model = new C3DModel(mesh, mtrls, tex);

	Object3D * tpot = new Object3D();
	tpot->Init(model);
	tpot->Move(0, 5, -5);
	ObjectManager.Add(tpot);

	//
	// add floor
	//
	LPDIRECT3DVERTEXBUFFER9 floor = nullptr;

	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		0, // usage
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&floor,
		0);

	TVertex* v = 0;
	floor->Lock(0, 0, (void**)&v, 0);

	v[0] = TVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f);
	v[1] = TVertex(-7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[2] = TVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f);

	v[3] = TVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f);
	v[4] = TVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f);
	v[5] = TVertex(7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f);

	floor->Unlock();
	D3DMATERIAL9 fmtrl = D3DMATERIAL9(WHITE_MTRL);
	ObjectBuffer* goFloor = new ObjectBuffer(floor, nullptr, TVertex::FVF, sizeof(TVertex), &fmtrl, FloorTex);
	goFloor->SetTag(string("floor"));
	goFloor->Move(0, 0, 0);
	ObjectManager.Add(goFloor);

	// 
	// add wall 1
	//
	LPDIRECT3DVERTEXBUFFER9 wall = nullptr;

	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		0, // usage
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&wall,
		0);

	v = 0;
	wall->Lock(0, 0, (void**)&v, 0);

	v[0] = TVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TVertex(-7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = TVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = TVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = TVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	wall->Unlock();
	D3DMATERIAL9 wmtrl = D3DMATERIAL9(WHITE_MTRL);
	ObjectBuffer* goWall = new ObjectBuffer(wall, nullptr, TVertex::FVF, sizeof(TVertex), &wmtrl, WallTex);

	ObjectManager.Add(goWall);
	goWall->SetTag(string("wall"));
	goWall->Move(0, 0, 0);
	
	//
	// add wall 2
	//
	LPDIRECT3DVERTEXBUFFER9 wall2 = nullptr;

	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		0, // usage
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&wall2,
		0);

	v = 0;
	wall2->Lock(0, 0, (void**)&v, 0);

	v[0] = TVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = TVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = TVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = TVertex(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	wall2->Unlock();
	D3DMATERIAL9 w2mtrl = D3DMATERIAL9(WHITE_MTRL);
	ObjectBuffer* goWall2 = new ObjectBuffer(wall2, nullptr, TVertex::FVF, sizeof(TVertex), &w2mtrl, WallTex);

	goWall2->SetTag(string("wall2"));
	ObjectManager.Add(goWall2);
	goWall2->Move(0, 0, 0);

	//
	// add mirror 
	//
	LPDIRECT3DVERTEXBUFFER9 mirror = nullptr;
	
	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		0, // usage
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&mirror,
		0);

	v = 0;
	mirror->Lock(0, 0, (void**)&v, 0);


	v[0] = TVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = TVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = TVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = TVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	mirror->Unlock();
	D3DMATERIAL9 mmtrl = D3DMATERIAL9(WHITE_MTRL);
	ObjectBuffer* goMirror = new ObjectBuffer(mirror, nullptr, TVertex::FVF, sizeof(TVertex), &mmtrl, MirrorTex);

	goMirror->SetTag(string("mirror"));
	ObjectManager.Add(goMirror);
	goMirror->Move(0, 0, 0);


	// mirror stencil

	LPDIRECT3DVERTEXBUFFER9 smirror = nullptr;

	device->CreateVertexBuffer(
		6 * sizeof(TVertex),
		0, // usage
		TVertex::FVF,
		D3DPOOL_MANAGED,
		&smirror,
		0);

	v = 0;
	smirror->Lock(0, 0, (void**)&v, 0);
	// mirror
	v[0] = TVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = TVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = TVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = TVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	smirror->Unlock();
	D3DMATERIAL9 smmtrl = D3DMATERIAL9(WHITE_MTRL);
	ObjectStencil *SMirror = new MirrorStencil(smirror, nullptr, TVertex::FVF, sizeof(TVertex), &smmtrl, nullptr);
	SMirror->Move(1, 1, 1);
	ObjectManager.Add(SMirror);
}