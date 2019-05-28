#pragma once
#include "Object.h"
#include "Renderer.h"
#include <memory>
//
// 2d 오브젝트는 텍스쳐를 자신이 가지고 있음
// sprite를 통해 바로 draw를 함
// 구식 메모리 처리에서 바꿔보기 위해 이거만 unique_ptr 사용해봄
//
class Rigidbody2D;
class CTexture;

class Object2D :
	public Object
{
	friend Rigidbody2D;
	//friend Collider2D;
	friend Renderer;
public:
	Object2D();
	~Object2D();

	virtual bool Init(CTexture* pTexture = nullptr);
	virtual void Draw(ID3DXSprite* sprite);
	virtual int Destroy() override;
	virtual int Update(float deltaTime) override { return true; };
	const D3DXCOLOR& GetColor() { return mColor; };
	void SetColor(const D3DXCOLOR& color) { mColor = color; };

private:
	std::unique_ptr<CTexture> mTexture;
	D3DXCOLOR mColor = 0xffffffff;
};

