#include <Novice.h>

#include "Player.h"
#include <memory>
#include <algorithm>

const char kWindowTitle[] = "LC1D_99_マエダ_イオリ_タイトル";

/// <summary>
/// 矩形の描画(画像)
/// </summary>
/// <param name="center">描画中心座標</param>
/// <param name="sizeHalf">描画範囲</param>
/// <param name="graphHandle">画像ハンドル</param>
/// <param name="color">色</param>
/// <param name="scale">倍率</param>
/// <param name="uvPosition">画像切り取り開始左上頂点</param>
/// <param name="drawArea">画像切り取り範囲</param>
void DrawRect(const Vector2 &center, const Vector2 &sizeHalf, int graphHandle, unsigned int color = WHITE, const Vector2 &scale = Vector2(1.0f, 1.0f), const Vector2 &uvPosition = Vector2(), const Vector2 &drawArea = Vector2(1.0f, 1.0f))
{
	Vector2 drawSize = { sizeHalf.x * scale.x, sizeHalf.y * scale.y };
	Novice::DrawQuad(
		static_cast<int>(center.x - drawSize.x),
		static_cast<int>(center.y - drawSize.y),
		static_cast<int>(center.x + drawSize.x),
		static_cast<int>(center.y - drawSize.y),
		static_cast<int>(center.x - drawSize.x),
		static_cast<int>(center.y + drawSize.y),
		static_cast<int>(center.x + drawSize.x),
		static_cast<int>(center.y + drawSize.y),
		static_cast<int>(uvPosition.x),
		static_cast<int>(uvPosition.y),
		static_cast<int>(drawArea.y),
		static_cast<int>(drawArea.y),
		graphHandle,
		color
	);
}

bool IsCollision(const Vector2&)
{
	return true;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	const int kWindowWidth = 640;
	const int kWindowHeight = 720;
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	using namespace std;
	const int kWhiteGraphHandle = Novice::LoadTexture("white1x1.png");
	const Vector2 kDrawMargin = { 10.0f, 10.0f };

	unique_ptr<Player> player = make_unique<Player>(Vector2(kWindowWidth / 2, kWindowHeight - 100), Vector2(32.0f, 32.0f), 10.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_W]) { player->MoveUp(); }
		if (keys[DIK_S]) { player->MoveDown(); }
		if (keys[DIK_A]) { player->MoveLeft(); }
		if (keys[DIK_D]) { player->MoveRight(); }
		player->Update();
		Vector2 clampPosition{
			clamp(player->GetPosition().x, 0.0f + player->GetSizeHalf().x + kDrawMargin.x, kWindowWidth - player->GetSizeHalf().x - kDrawMargin.x),
			clamp(player->GetPosition().y, 0.0f + player->GetSizeHalf().y + kDrawMargin.y, kWindowHeight - player->GetSizeHalf().y - kDrawMargin.y)
		};
		player->SetPosition(clampPosition);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawRect(player->GetPosition(), player->GetSizeHalf(), kWhiteGraphHandle, 0x00aaaaff);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
