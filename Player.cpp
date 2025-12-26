#include "Player.h"
#include <algorithm>
#include <memory>
#include <numbers>
#include <cmath>

#include "NoviceUtility.h"
#include "ObjectsManager.h"
#include "BaseMob.h"
#include "BaseItem.h"

void Player::OnCollision(const GameObject& obj)
{
	switch (obj.GetTag())
	{
	case ObjectTag::Enemy:
		mHp--;
		break;
	case ObjectTag::Item:
	{
		const BaseMob& mob = static_cast<const BaseMob&>(obj);
		if (mob.IsDangerous())
		{
			mHp--;
			break;
		}
		else
		{
			const BaseItem& item = static_cast<const BaseItem&>(mob);
			UpGrade(item.GetItemType(), item.GetLevel());

		}
	}
	break;
	default:
		break;
	}

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

	if (Vector2::Normalize(mMoveDir).Length() <= 0.0f) { return; }
	mBulletConfig.moveDir = mMoveDir;
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
	//mMaxBulletCount = 10;
	float pi = std::numbers::pi_v<float>;
	float centerAngle = pi / 2.0f; // 真上 (0, -1)
	float spread = pi;       // 左右に45度ずつ広げる例

	for (int i = 0; i <= mMaxBulletCount; i++) {
		// -spread から +spread までを分割する
		float offset = -spread + (spread * 2.0f / (mMaxBulletCount)) * i;
		float angle = centerAngle + offset;

		Vector2 dir = { std::cosf(angle), std::sinf(angle) };

		mBulletConfig.moveDir = dir; // Normalize不要
		mBulletConfig.centerPosition = mCenterPosition + dir * mSizeHalf.x;

		ObjectsManager::AddGameObject(std::make_unique<Bullet>(mBulletConfig));
	}
}

void Player::UpGrade(ItemType type, int level)
{
	switch (type)
	{
	case ItemType::None:
		break;
	case ItemType::BulletUpgrade:
		mMaxBulletCount++;
		break;
	case ItemType::Heal:
		mHp += level;
		break;
	default:
		break;
	}
}
