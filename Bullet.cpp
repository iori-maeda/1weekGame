#include "Bullet.h"
#include "NoviceUtility.h"

void Bullet::OnCollision(const GameObject &obj)
{
	bool checkCollisionType = obj.CompareTag(ObjectTag::Item) || obj.CompareTag(ObjectTag::Enemy);


	if(checkCollisionType)
	{
		mIsActive = false;
	}
}

void Bullet::Update()
{
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;

	if(mCenterPosition.y < -mSizeHalf.y || mCenterPosition.y > NoviceUtility::kWindowHeight + mSizeHalf.y ||
	   mCenterPosition.x < -mSizeHalf.x || mCenterPosition.x > NoviceUtility::kWindowWidth + mSizeHalf.x)
	{
		mIsActive = false;
	}
}