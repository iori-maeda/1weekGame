#include "Player.h"
#include <algorithm>
#include <memory>

#include "NoviceUtility.h"
#include "ObjectsManager.h"

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
	Vector2 clampPosition{
			std::clamp(mCenterPosition.x, 0.0f + mSizeHalf.x + NoviceUtility::kDrawMargin.x, NoviceUtility::kWindowWidth - mSizeHalf.x - NoviceUtility::kDrawMargin.x),
			std::clamp(mCenterPosition.y, 0.0f + mSizeHalf.y + NoviceUtility::kDrawMargin.y, NoviceUtility::kWindowHeight - mSizeHalf.y - NoviceUtility::kDrawMargin.y)
	};
	mCenterPosition = clampPosition;
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
	mBulletConfig.centerPosition = mCenterPosition;
	std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(mBulletConfig);
	ObjectsManager::AddGameObject(std::move(bullet));
}