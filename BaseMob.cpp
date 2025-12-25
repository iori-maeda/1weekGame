#include "BaseMob.h"

void BaseMob::OnCollision(const GameObject &obj)
{
	if (!obj.CompareTag(ObjectTag::Player)) { return; }
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

void BaseMob::Idol()
{
	mCurrentState = State::Move;
}

void BaseMob::Move()
{
	mMoveDir = { 0.0f ,1.0f };

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
}

void BaseMob::Spawn()
{
	mCurrentState = State::Idol;
	if (mIsActive) { return; }

	mIsActive = true;
}