#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "BaseMob.h"
#include "Bullet.h"

enum class ItemType
{
	None,
	BulletUpgrade,
	Heal
};

struct BaseItemConfig : public BaseMobConfig
{
	ItemType type = ItemType::None;
	float maxDangerousTime = 2.0f;
	unsigned int dangerousColor = 0xff0000ff;
	int level = 1;
	int maxHp = 1;
};

class BaseItem : public BaseMob
{
public:
	BaseItem(const BaseItemConfig &config)
		:BaseMob(config), mMaxDangerousTime(config.maxDangerousTime), mLevel(config.level), mMaxHp(config.hp), mBaseColor(config.color), mDangerousColor(config.dangerousColor)
	{};

	void Update() override;
	void OnCollision(const GameObject &obj) override;

public:

	int GetLevel()const { return mLevel; }
	ItemType GetItemType()const { return mType; }


private:
	void ToWards(const Vector2 &targetPosition);

private:
	ItemType mType = ItemType::None;
	const float mMaxDangerousTime = 2.0f;
	float mDangerousTimer = 0.0f;
	int mLevel = 1;
	const int mMaxHp = 1;
	const unsigned int mBaseColor = 0x000000ff;
	const unsigned int mDangerousColor = 0xff0000ff;
};