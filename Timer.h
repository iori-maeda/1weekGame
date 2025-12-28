#pragma once

enum class TimerCountPettern : int
{
	ADD = 1,
	SUBTRACT = -1
};

class Timer
{
public:
	void Initialize(float limitTime, TimerCountPettern pattern);
	void Start() { mIsCounting = true; }
	void Update();
	void Reset();

	bool isCounting() const { return mIsCounting; }
	float GetTimeRate() const { return mPattern == TimerCountPettern::ADD ? mTimer / mLimitTime : 1.0f - (mTimer / mLimitTime); }
	float GetLimitTime() const { return mLimitTime; }
	float GetDeltaTime() const { return 1.0f / 60.0f; }

private:

	bool mIsCounting = false;
	TimerCountPettern mPattern = TimerCountPettern::SUBTRACT;
	float mLimitTime = 1.0f;
	float mTimer= 0.0f;
};

