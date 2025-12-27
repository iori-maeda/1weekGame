#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "Bullet.h"
#include "BaseItem.h"

struct PlayerConfig : public GameObjectConfig
{
	int hp = 10;
	float speed = 1.0f;
	float shotInterval = 1.0f;
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
		:GameObject(config), mHp(config.hp), mSpeed(config.speed), mShotIntervalTime(config.shotInterval), mShotIntervalTimer(0.0f), mMaxBulletCount(1)
	{};

	void OnCollision(const GameObject &obj) override;

	void Update() override;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Fire();

public:
	void SetBuletConfig(const BulletConfig &config) { mBulletConfig = config; }

private:
	void UpGrade(ItemType type, int level);

private:
	int mHp = 10;
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};

	float mShotIntervalTime = 1.0f;
	float mShotIntervalTimer = 0.0f;
	int mMaxBulletCount = 1;

	BulletConfig mBulletConfig{};
};