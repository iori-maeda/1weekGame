#pragma once
#include "GameObject.h"

namespace NoviceUtility
{
	const int kWindowWidth = 640;
	const int kWindowHeight = 720;
	inline int kWhiteGraphHandle;
	const Vector2 kDrawMargin = { 10.0f, 10.0f };

	/// <summary>
	/// 
	/// </summary>
	/// <param name="obj">描画オブジェクトの情報</param>
	/// <param name="graphHandle">画像ハンドル</param>
	/// <param name="color">色</param>
	/// <param name="scale">倍率</param>
	/// <param name="uvPosition">画像切り取り開始左上頂点</param>
	/// <param name="drawArea">画像切り取り範囲</param>
	void DrawSprite(
		const GameObject& obj,
		int graphHandle,
		const Vector2& uvPosition = Vector2(),
		const Vector2& drawArea = Vector2(1.0f, 1.0f),
		const Vector2& scale = Vector2(1.0f, 1.0f)
	);
};