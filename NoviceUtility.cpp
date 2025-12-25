#include "NoviceUtility.h"
#include <Novice.h>

namespace NoviceUtility
{
	void DrawSprite(
		const GameObject& obj,
		int graphHandle,
		const Vector2& uvPosition,
		const Vector2& drawArea,
		const Vector2& scale
	)
	{
		Vector2 drawSize = { obj.GetSizeHalf().x * scale.x, obj.GetSizeHalf().y * scale.y };
		Novice::DrawQuad(
			static_cast<int>(obj.GetPosition().x - drawSize.x),
			static_cast<int>(obj.GetPosition().y - drawSize.y),
			static_cast<int>(obj.GetPosition().x + drawSize.x),
			static_cast<int>(obj.GetPosition().y - drawSize.y),
			static_cast<int>(obj.GetPosition().x - drawSize.x),
			static_cast<int>(obj.GetPosition().y + drawSize.y),
			static_cast<int>(obj.GetPosition().x + drawSize.x),
			static_cast<int>(obj.GetPosition().y + drawSize.y),
			static_cast<int>(uvPosition.x),
			static_cast<int>(uvPosition.y),
			static_cast<int>(drawArea.x),
			static_cast<int>(drawArea.y),
			graphHandle,
			obj.GetColor()
		);
	}
}