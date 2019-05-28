#pragma once
#include "Object.h"
#include "Renderer.h"
#include <memory>
//
// 2d ������Ʈ�� �ؽ��ĸ� �ڽ��� ������ ����
// sprite�� ���� �ٷ� draw�� ��
// ���� �޸� ó������ �ٲ㺸�� ���� �̰Ÿ� unique_ptr ����غ�
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

