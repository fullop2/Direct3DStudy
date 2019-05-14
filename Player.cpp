#include "Player.h"
#include "Object2D.h"
#include "Window.h"


Player::Player()
	:Object2D()
{
}


Player::~Player()
{
}

int Player::Update()
{
	if (GetKeyDown('W'))
		mPosition.y -= 3;
	if (GetKeyDown('S'))
		mPosition.y += 3;
	if (GetKeyDown('A'))
		mPosition.x -= 3;
	if (GetKeyDown('D'))
		mPosition.x += 3;

	return true;
}