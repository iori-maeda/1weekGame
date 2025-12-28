#include "Timer.h"

void Timer::Initialize(float limitTime, TimerCountPettern pattern)
{
	mPattern = pattern;
	mLimitTime = limitTime;
	Reset();
}

void Timer::Update()
{
	if (!mIsCounting) { return; }
	mTimer += static_cast<float>(mPattern) / 60.0f;
	if (mTimer <= 0.0f) { mIsCounting = false; }
}

void Timer::Reset()
{
	mTimer = mPattern == TimerCountPettern::SUBTRACT ? mLimitTime : 0.0f;
}