#pragma once
#include "Vector2.h"

class BaseEnemy
{
	enum class State
	{
		Idol = 0,
		Move = 1,
		Attack = 2,
		Dead = 3,
		Spawn = 4
	};

public:
	BaseEnemy()
		:mIsActive(true), mCenterPosition{}, mSizeHalf{ 32.0f, 32.0f }, mSpeed(1.0f)
	{};

	BaseEnemy(const Vector2 &position, const Vector2 &sizeHalf, float speed, bool isActive = true)
		:mIsActive(isActive), mCenterPosition(position), mSizeHalf(sizeHalf), mSpeed(speed)
	{};

	void StateUpdate();

private:
	void Idol();
	void Move();
	void Attack();
	void Dead();
	void Spawn();

private:
	bool mIsActive = true;
	Vector2 mCenterPosition{};
	Vector2 mSizeHalf{};
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};

	State mCurrentState = State::Spawn;
};

