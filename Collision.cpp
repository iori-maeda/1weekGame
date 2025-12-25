#include "Collision.h"

bool Collision::AABB(const GameObject& obj1, const GameObject& obj2)
{
	Vector2 obj1Min = obj1.GetPosition() - obj1.GetSizeHalf();
	Vector2 obj1Max = obj1.GetPosition() + obj1.GetSizeHalf();
	Vector2 obj2Min = obj2.GetPosition() - obj2.GetSizeHalf();
	Vector2 obj2Max = obj2.GetPosition() + obj2.GetSizeHalf();

	bool isHitX = obj1Min.x <= obj2Max.x && obj1Max.x >= obj2Min.x;
	bool isHitY = obj1Min.y <= obj2Max.y && obj1Max.y >= obj2Min.y;

	return isHitX && isHitY;
}
