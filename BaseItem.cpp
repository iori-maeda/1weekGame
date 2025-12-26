#include "BaseItem.h"
#include "Collision.h"

void BaseItem::Update()
{
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;

	if (!Collision::AABB_ToScreen(*this))
	{
		mIsActive = false;
		return;
	}
	mColor = mBaseColor;
	if (!mIsDangerous) { return; }
	mDangerousTimer -= 1.0f / 60.0f;
	mColor = mDangerousColor;
	if (mDangerousTimer <= 0.0f) { mIsDangerous = false; }
}

void BaseItem::OnCollision(const GameObject& obj)
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
		if (mIsDangerous) { break; }
		mIsDangerous = true;
		mDangerousTimer = mMaxDangerousTime;
		mLevel++;
		mHp = mLevel * mMaxHp;
		if (mTargetPlayer)
		{
			ToWards();
		}
		break;

	default:
		break;
	}
}

void BaseItem::ToWards()
{
	Vector2 toTarget = mTargetPlayer->GetPosition() - mCenterPosition;
	mMoveDir = Vector2::Normalize(toTarget);
	mCenterPosition += mMoveDir * mSpeed * 2.0f;
}