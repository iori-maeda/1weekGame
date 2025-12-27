#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "BaseMob.h"

struct BulletConfig : public BaseMobConfig
{
	int damage = 1;
};

class Bullet : public BaseMob
{
public:
	Bullet(ObjectTag tag, const Vector2 &position, const Vector2 &sizeHalf, int hp, float speed, unsigned int color = 0xffffffff, bool isActive = true, bool isDangerous = false)
		:BaseMob(tag, position, sizeHalf, hp, speed, color, isActive, isDangerous)
	{};

	Bullet(const BulletConfig &config)
		:BaseMob(config)
	{};

	void OnCollision(const GameObject& obj) override;

	void Update() override;
};

