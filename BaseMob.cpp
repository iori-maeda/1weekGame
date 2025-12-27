#include "BaseMob.h"
#include "ObjectsManager.h"
#include "BaseItem.h"
#include "NoviceUtility.h"
#include "Collision.h"

GameObject* BaseMob::mTargetPlayer = nullptr;

void BaseMob::OnCollision(const GameObject &obj)
{
	if (!obj.CompareTag(ObjectTag::Player) && !obj.CompareTag(ObjectTag::PlayerBullet) ) { return; }
	const BaseMob &mob = static_cast<const BaseMob &>(obj);
	if (!mob.mIsDangerous) { return; }
	mHp--;
	if (mHp <= 0) { mCurrentState = State::Dead; }
}

void BaseMob::Update()
{
	StateUpdate();
}

void BaseMob::StateUpdate()
{
	if (!mIsActive) { return; }

	switch (mCurrentState)
	{
	case BaseMob::State::Idol:
		Idol();
		break;
	case BaseMob::State::Move:
		Move();
		break;
	case BaseMob::State::Attack:
		break;
	case BaseMob::State::Dead:
		Dead();
		break;
	case BaseMob::State::Spawn:
		Spawn();
		break;
	default:
		break;
	}
}

void BaseMob::SelfKill()
{
	mCurrentState = State::Dead;
}

void BaseMob::SetTargetPtr(GameObject* target)
{
	mTargetPlayer = target;
}

void BaseMob::Idol()
{
	mCurrentState = State::Move;
}

void BaseMob::Move()
{
	if(mTargetPlayer)
	{
		Vector2 toPlayerDir = Vector2::Normalize(mTargetPlayer->GetPosition() - mCenterPosition);
		mMoveDir = toPlayerDir;
	}
	mCenterPosition += Vector2::Normalize(mMoveDir) * mSpeed;
}

void BaseMob::Attack()
{
	mCurrentState = State::Idol;
}

void BaseMob::Dead()
{
	if (!mIsActive) { return; }

	mIsActive = false;

	ObjectsManager::CreateItem(mCenterPosition, ItemType::BulletUpgrade);
}

void BaseMob::Spawn()
{
	if(!Collision::AABB_ToScreen(*this))
	{
		Move();
		return;
	}

	mCurrentState = State::Idol;
}