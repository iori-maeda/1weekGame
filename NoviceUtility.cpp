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
	void DrawDebugObjectInformation(const Vector2& position, const GameObject& info)
	{
		Novice::ScreenPrintf(
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			"Tag:%d Pos:(%.1f,%.1f) Size:(%.1f,%.1f) Active:%d",
			static_cast<int>(info.GetTag()),
			info.GetPosition().x, info.GetPosition().y,
			info.GetSizeHalf().x, info.GetSizeHalf().y,
			static_cast<int>(info.IsActive())
		);
	}
}