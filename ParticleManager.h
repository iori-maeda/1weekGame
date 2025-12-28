#pragma once

#include <memory>
#include <array>
#include <functional>

#include "Vector2.h"
#include "GameObject.h"
#include "Timer.h"

struct EasingParam
{
	Vector2 startPos{};
	Vector2 endPos{};
	std::function<float(float)> func = nullptr;
};

struct ParticleConfig : public GameObjectConfig
{
	float speed = 1.0f;
	Vector2 moveDir{};
	float maxLifeTime = 1.0f;
	bool isAcceleration = false;
	Vector2 acceleration{};
};


class Particle : public GameObject
{
public:

public:
	Particle() = default;
	Particle(const ParticleConfig& config)
		:GameObject(config), mSpeed(config.speed), mMoveDir(config.moveDir), mEmittColor(config.color), mAcceleration(config.isAcceleration ? config.acceleration : Vector2{})
	{
		mLifeTimer = std::make_unique<Timer>();
		mLifeTimer->Initialize(config.maxLifeTime, TimerCountPettern::SUBTRACT);
		mLifeTimer->Reset();
		mLifeTimer->Start();
	};
	void Update() override;
	void SetEasingStatus(const Vector2& start, const Vector2& end, std::function<float(float)> func) { mEasingParam_.startPos = start, mEasingParam_.endPos = end, mEasingParam_.func = func; }

private:
	std::unique_ptr<Timer> mLifeTimer;

	Vector2 mMoveDir{};
	const float mSpeed = 0.0f;
	Vector2 mVelocity{};
	Vector2 mAcceleration{};

	EasingParam mEasingParam_{};
	unsigned int mEmittColor = 0xffffffff;
};


class ParticleManager
{
public:

	ParticleManager() = default;
	~ParticleManager() = default;

	void Initialize(const Vector2& emitCenter, const Vector2& emitArea);
	void Update();

	void Emittion(const ParticleConfig& config, int emittionNum = 1);

public:

	void SetEmittionPosition(const Vector2& pos) { mEmittCenter = pos; }

private:

	Vector2 mEmittCenter{};
	Vector2 mEmittAreaSize{ 1.0f, 1.0f };

	std::unique_ptr<Timer> mEmittionInterval;
};