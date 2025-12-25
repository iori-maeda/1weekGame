#pragma once
#include "Vector2.h"
#include "GameObject.h"

struct PlayerConfig : public GameObjectConfig
{
	int hp = 10;
	float speed = 1.0f;
};

class Player : public GameObject
{
public:
	Player()
		:mSpeed(1.0f), mMoveDir{}
	{};

	Player(ObjectTag tag, const Vector2 &position, const Vector2 &sizeHalf, int hp, float speed, unsigned int color = 0xffffffff, bool isActive = true)
		:GameObject(tag, position, sizeHalf, color, isActive), mHp(hp), mSpeed(speed)
	{};

	Player(const PlayerConfig &config)
		:GameObject(config), mHp(config.hp), mSpeed(config.speed)
	{};

	void OnCollision(const GameObject &obj) override;

	void Update();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Fire();

private:
	int mHp = 10;
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};
};