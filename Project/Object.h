#pragma once
#include "stdafx.h"

//
// 모든 게임 오브젝트는 위치, 회전방향, 크기비율을 가지고 있음
// available == false 일 경우 화면에 draw하지 않음
// 업데이트 실패(false) 시 객체 삭제
//

class Object
{
public:
	Object();
	virtual ~Object()
	{

	};

	const bool GetAvailable()			{ return mbAvailable; };
	const D3DXVECTOR3& GetPosition()	{ return mPosition; };
	const D3DXVECTOR3& GetRotation()	{ return mRotation; };
	const D3DXVECTOR3& GetScale()		{ return mScale; };
	const string& GetTag()				{ return mTag; };

	void Move			(D3DXVECTOR3 position);
	void Move			(float x, float y, float z = 0);
	void MoveRelative	(D3DXVECTOR3 displacement);
	void MoveRelative	(float x, float y, float z = 0);
	void Rotate			(D3DXVECTOR3 rotation);
	void Rotate			(float x, float y, float z = 0);
	void SetScale		(D3DXVECTOR3 scale);
	void SetTag			(string& tag) { mTag = tag; };

	virtual int Update(float deltaTime) { return true; };
	virtual int Destroy() { return true; };

protected:
	string		mTag;
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mRotation;
	D3DXVECTOR3 mScale;
	bool		mbAvailable;

};

