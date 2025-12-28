#include "EasingFunction.h"
#define _USE_MATH_DEFINES
#include <cmath>

float EasingFunction::Linear(float t)
{
	return t;
}

float EasingFunction::EaseInQuad(float t)
{
	return t * t;
}

float EasingFunction::EaseOutQuad(float t)
{
	return 1.0f - (1.0f - t) * (1.0f - t);
}

float EasingFunction::EaseInOutQuad(float t)
{
	return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

float EasingFunction::EaseInCubic(float t)
{
	return t * t * t;
}

float EasingFunction::EaseOutCubic(float t)
{
	return 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t);
}

float EasingFunction::EaseInOutCubic(float t)
{
	return t < 0.5f ? 4.0f * t * t * t : 1.0f - std::powf(-2.0f * t + 2.0f, 3) / 2.0f;
}

float EasingFunction::EaseInQuart(float t)
{
	return t * t * t * t;
}

float EasingFunction::EaseOutQuart(float t)
{
	return 1.0f - std::powf(1.0f - t, 4.0f);
}

float EasingFunction::EaseInOutQuart(float t)
{
	return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - std::powf(-2.0f * t + 2.0f, 4) / 2.0f;
}

float EasingFunction::EaseInQuint(float t)
{
	return t * t * t * t * t;
}

float EasingFunction::EaseOutQuint(float t)
{
	return 1.0f - std::powf(1.0f - t, 5.0f);
}

float EasingFunction::EaseInOutQuint(float t)
{
	return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - std::powf(-2.0f * t + 2.0f, 5) / 2.0f;
}

float EasingFunction::EaseInSine(float t)
{
	return 1.0f - std::cosf((t * static_cast<float>(M_PI)) / 2.0f);
}

float EasingFunction::EaseOutSine(float t)
{
	return std::sinf((t * static_cast<float>(M_PI)) / 2.0f);
}

float EasingFunction::EaseInOutSine(float t)
{
	return -(std::cosf(static_cast<float>(M_PI) * t) - 1.0f) / 2.0f;
}

float EasingFunction::EaseInExpo(float t)
{
	return t == 0.0f ? 0.0f : std::powf(2.0f, 10.0f * t - 10.0f);
}

float EasingFunction::EaseOutExpo(float t)
{
	return t == 1.0f ? 1.0f : 1.0f - std::powf(2.0f, -10.0f * t);
}

float EasingFunction::EaseInOutExpo(float t)
{
	if (t == 0.0f) return 0.0f;
	if (t == 1.0f) return 1.0f;
	return t < 0.5f ? std::powf(2.0f, 20.0f * t - 10.0f) / 2.0f : (2.0f - std::powf(2.0f, -20.0f * t + 10.0f)) / 2.0f;
}

float EasingFunction::EaseInCirc(float t)
{
	return 1.0f - std::sqrtf(1.0f - t * t);
}

float EasingFunction::EaseOutCirc(float t)
{
	return std::sqrtf(1.0f - (t - 1.0f) * (t - 1.0f));
}

float EasingFunction::EaseInOutCirc(float t)
{
	return t < 0.5f ? (1.0f - std::sqrtf(1.0f - 4.0f * t * t)) / 2.0f : (std::sqrtf(1.0f - std::powf(-2.0f * t + 2.0f, 2)) + 1.0f) / 2.0f;
}
