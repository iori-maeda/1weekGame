#pragma once
#include "Vector2.h"
#include "GameObject.h"

struct BaseMobConfig : public GameObjectConfig
{
	int hp = 1;
	float speed = 1.0f;
	Vector2 moveDir = { 0.0f, 1.0f };
	bool isDangerous = false;
};

class BaseMob : public GameObject
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
	BaseMob()
		:mSpeed(1.0f), mMoveDir{}
	{};

	BaseMob(ObjectTag tag, const Vector2 &position, const Vector2 &sizeHalf, int hp, float speed, unsigned int color = 0xffffffff, bool isActive = true, bool isDangerous = false)
		:GameObject(tag, position, sizeHalf, color, isActive), mHp(hp), mIsDangerous(isDangerous), mSpeed(speed)
	{};

	BaseMob(const BaseMobConfig &config)
		:GameObject(config), mHp(config.hp), mIsDangerous(config.isDangerous), mSpeed(config.speed), mMoveDir(config.moveDir)
	{};

	void OnCollision(const GameObject &obj) override;

	void Update() override;
	void StateUpdate();
	void SelfKill();

public:

	bool IsDangerous()const { return mIsDangerous; }

private:
	virtual void Idol();
	virtual void Move();
	virtual void Attack();
	virtual void Dead();
	virtual void Spawn();

protected:
	int mHp = 10;
	bool mIsDangerous = false;
	const float mSpeed = 1.0f;
	Vector2 mMoveDir{};

	State mCurrentState = State::Spawn;
};

