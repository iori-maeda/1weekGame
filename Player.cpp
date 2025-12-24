#include "Player.h"

void Player::Update()
{
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;

	mMoveDir = {};
}

void Player::MoveLeft()
{
	mMoveDir.x = -1.0f;
}

void Player::MoveRight()
{
	mMoveDir.x = 1.0f;
}

void Player::MoveUp()
{
	mMoveDir.y = -1.0f;
}

void Player::MoveDown()
{
	mMoveDir.y = 1.0f;
}