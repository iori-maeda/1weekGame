#include "BaseItem.h"

void BaseItem::Update()
{
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;
	mColor = mBaseColor;
	if (!mIsDangerous) { return; }
	mDangerousTimer -= 1.0f / 60.0f;
	mColor = mDangerousColor;
	if (mDangerousTimer <= 0.0f) { mIsDangerous = false; }
}

void BaseItem::OnCollision(const GameObject &obj)
{
	switch (obj.GetTag())
	{
	case ObjectTag::Player:
		if (!mIsDangerous)
		{
			mIsActive = false;
		}
		break;

	case ObjectTag::PlayerBullet:
		mHp--;
		mIsDangerous = true;
		mDangerousTimer = mMaxDangerousTime;
		mLevel++;
		mHp = mLevel * mMaxHp;
		ToWards(obj.GetPosition());
		break;

	default:
		break;
	}
}

void BaseItem::ToWards(const Vector2 &targetPosition)
{
	Vector2 toTarget = targetPosition - mCenterPosition;

	mCenterPosition += Vector2::Normalize(toTarget) * mSpeed * 2.0f;
}