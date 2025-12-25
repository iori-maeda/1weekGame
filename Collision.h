#pragma once
#include "GameObject.h"

class Collision
{
public:
	static bool AABB(const GameObject& obj1, const GameObject& obj2);
};

