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

	GameObject(const Vector2 &position, const Vector2 &sizeHalf, bool isActive = true)
		:mIsActive(isActive), mCenterPosition(position), mSizeHalf(sizeHalf)
	{};

private:

	Tag mTag = Tag::None;
	bool mIsActive = true;
	Vector2 mCenterPosition{};
	Vector2 mSizeHalf{};

	unsigned int mColor = 0xffffffff;
};

