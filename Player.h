#pragma once
#include "Vector2.h"

class Player
{
public:
	Player()
		:mIsActive(true), mCenterPosition{}, mSizeHalf{ 32.0f, 32.0f }, mSpeed(1.0f)
	{};

	Player(const Vector2 &position, const Vector2 &sizeHalf, float speed, bool isActive = true)
		:mIsActive(isActive), mCenterPosition(position), mSizeHalf(sizeHalf), mSpeed(speed)
	{};

	void Update();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	/*void MoveLeftTop();
	void MoveLeftBottom();
	void MoveRightTop();
	void MoveRightBottom();*/

public:
	bool IsActive() const { return mIsActive; }
	Vector2 GetPosition() const { return mCenterPosition; }
	Vector2 GetSizeHalf() const { return mSizeHalf; }

	void SetPosition(const Vector2 &position) { mCenterPosition = position; }

private:
	bool mIsActive = true;
	Vector2 mCenterPosition{};
	Vector2 mSizeHalf{};
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};
};