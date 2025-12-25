#include "Bullet.h"

void Bullet::OnCollision(const GameObject &obj)
{
	bool checkCollisionType = obj.CompareTag(ObjectTag::Item) || obj.CompareTag(ObjectTag::Enemy);
	bool isPlayerBullet = this->CompareTag(ObjectTag::Player);


	if(checkCollisionType && isPlayerBullet)
	{
		mIsActive = false;
	}
}

void Bullet::Update()
{
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;
}