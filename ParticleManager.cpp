#include "ParticleManager.h"

#include <numbers>
#include <cmath>

#include "Random.h"
#include "EasingFunction.h"
#include "ObjectsManager.h"
#include "Collision.h"

void Particle::Update()
{
	if (!mIsActive) { return; }
	if (!mLifeTimer->isCounting())
	{
		mIsActive = false;
		return;
	}

	mLifeTimer->Update();

	if (mEasingParam_.func == nullptr)
	{
		mVelocity = Vector2::Normalize(mMoveDir) * mSpeed + mAcceleration;
		mCenterPosition += mVelocity;
	}
	else
	{
		mCenterPosition = Vector2::Lerp(mEasingParam_.startPos, mEasingParam_.endPos, mEasingParam_.func(mLifeTimer->GetTimeRate()));
	}

	int emittAlpha = mEmittColor & 0x000000ff;
	int alpha = static_cast<int>(static_cast<float>(emittAlpha) * mLifeTimer->GetTimeRate());;
	if (alpha > emittAlpha) { alpha = emittAlpha; }
	mColor = mEmittColor - alpha;
}

void ParticleManager::Initialize(const Vector2& emitCenter, const Vector2& emitArea)
{
	mEmittCenter = emitCenter;
	mEmittAreaSize = emitArea;
}

void ParticleManager::Emittion(const ParticleConfig& config, int emittionNum)
{
	ParticleConfig emitConfig = config;
	emitConfig.tag = ObjectTag::Particle;
	for (int i = 0; i < emittionNum; i++)
	{
		Vector2 randomOffset = Vector2(
			Random::GetRandom(-mEmittAreaSize.x / 2.0f, mEmittAreaSize.x / 2.0f),
			Random::GetRandom(-mEmittAreaSize.y / 2.0f, mEmittAreaSize.y / 2.0f)
		);
		emitConfig.centerPosition = mEmittCenter + randomOffset;
		std::unique_ptr<Particle> newParticle = std::make_unique<Particle>(emitConfig);

		ObjectsManager::AddGameObject(std::move(newParticle));
	}
}