#pragma once
#include "ObjectBuffer.h"
class ObjectStencil :
	public ObjectBuffer
{
public:
	virtual void Draw(LPDIRECT3DDEVICE9& device) override = 0;
	virtual ~ObjectStencil();
	ObjectStencil();
protected:
	
	
};

