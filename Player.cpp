#include "Player.h"

void Player::OnCollision(const GameObject &obj)
{
	if (!obj.CompareTag(ObjectTag::Enemy)) { return; }
	mHp--;
	if (mHp <= 0) { mIsActive = false; }
}

void Player::Update()
{
	if (!mIsActive) { return; }
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

void Player::Fire()
{

}