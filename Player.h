#pragma once
#include "Vector2.h"

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player()
		:mSpeed(1.0f), mMoveDir{}
	{
	};

	Player(const Vector2& position, const Vector2& sizeHalf, float speed, unsigned int color = 0xffffffff, bool isActive = true)
		:GameObject(position, sizeHalf, color, isActive), mSpeed(speed)
	{
	};

	void Update();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};
};