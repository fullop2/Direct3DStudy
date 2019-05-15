#pragma once
#include <d3dx9.h>


// particle 
struct Particle
{
	D3DXVECTOR3 _position;
	D3DCOLOR _color;
	static const DWORD FVF;
};

// attr
struct Attribute
{
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
	float _lifeTime;
	float _age;
	D3DXCOLOR _color;
	D3DXCOLOR _colorFade;
	bool _isAlive;
};

// xyz vector
struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
		:_x(x), _y(y), _z(z)
	{}

	float _x, _y, _z;
	static const DWORD FVF;
};

// xyz, color vector
struct CVertex
{
	CVertex() {}
	CVertex(float x, float y, float z, D3DCOLOR color)
		:_x(x), _y(y), _z(z), _color(color)
	{}

	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};

// xyz, normal vector
struct LVertex
{
	LVertex() {}
	LVertex(float x, float y, float z, float nx, float ny, float nz)
		:_x(x), _y(y), _z(z), _nx(nx), _ny(ny), _nz(nz)
	{}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	static const DWORD FVF;
};

// xyz, normal vector, uv vector
struct TVertex
{
	TVertex() {}
	TVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
		:_x(x), _y(y), _z(z), _nx(nx), _ny(ny), _nz(nz), _u(u), _v(v)
	{}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;
	static const DWORD FVF;
};

struct TerrainVertex
{
	TerrainVertex(){}
	TerrainVertex(float x, float y, float z, float u, float v)
		:_x(x), _y(y), _z(z), _u(u), _v(v)
	{}

	float _x, _y, _z;
	float _u, _v;
	static const DWORD FVF;

};



enum _VERTEXTYPE
{
	VERTEXTYPE_POSITION = 0x1,
	VERTEXTYPE_COLOR = 0x2,
	VERTEXTYPE_POSCOLOR = 0x3,
	VERTEXTYPE_NORMAL = 0x4,
	VERTEXTYPE_POSNORMAL = 0x5,
	VERTEXTYPE_TEXTURE = 0x8,
	VERTEXTYPE_POSNORTEX = 0x13
};

