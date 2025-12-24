#pragma once
#include "Vector2.h"
class GameObject
{
	enum class Tag
	{
		None,
		Player,
		Enemy,
		Item
	};

public:
	GameObject()
		:mIsActive(true), mCenterPosition{}, mSizeHalf{ 32.0f, 32.0f }
	{};

	GameObject(const Vector2 &position, const Vector2 &sizeHalf,unsigned int color = 0xffffffff, bool isActive = true)
		:mIsActive(isActive), mCenterPosition(position), mSizeHalf(sizeHalf), mColor(color)
	{};

public:
	bool IsActive() const { return mIsActive; }
	Vector2 GetPosition() const { return mCenterPosition; }
	Vector2 GetSizeHalf() const { return mSizeHalf; }

	void SetPosition(const Vector2& position) { mCenterPosition = position; }

protected:
	Tag mTag = Tag::None;
	bool mIsActive = true;
	Vector2 mCenterPosition{};
	Vector2 mSizeHalf{};

	unsigned int mColor = 0xffffffff;
};

