#include <Novice.h>

#include "Player.h"
#include "BaseMob.h"
#include "Bullet.h"
#include <memory>
#include <algorithm>
#include "NoviceUtility.h"
#include "ObjectsManager.h"
#include "Collision.h"
#include "EnemySporner.h"

const char kWindowTitle[] = "LC1D_99_マエダ_イオリ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, NoviceUtility::kWindowWidth, NoviceUtility::kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	using namespace std;

	NoviceUtility::kWhiteGraphHandle = Novice::LoadTexture("white1x1.png");

	unique_ptr<Player> player = make_unique<Player>(ObjectTag::Player, Vector2(NoviceUtility::kWindowWidth / 2, NoviceUtility::kWindowHeight - 100), Vector2(16.0f, 16.0f), 10, 10.0f, 0x00aaaaff);
	unique_ptr<BaseMob> startMob = make_unique<BaseMob>(ObjectTag::Enemy, Vector2(NoviceUtility::kWindowWidth / 2, 100), Vector2(16.0f, 16.0f), 1, 0.1f, 0xaaaa00ff);

	Player* playerPtr = player.get();
	BaseMob::SetTargetPtr(playerPtr);

	BulletConfig bulletConfig{};
	
	bulletConfig.isActive = true;
	bulletConfig.isDangerous = true;
	bulletConfig.centerPosition = player->GetPosition();
	bulletConfig.color = 0x0008888ff;
	bulletConfig.sizeHalf = Vector2(5.0f, 15.0f);
	bulletConfig.speed = 10.0f;
	bulletConfig.tag = ObjectTag::PlayerBullet;
	bulletConfig.moveDir = Vector2(0.0f, -1.0f);
	playerPtr->SetBuletConfig(bulletConfig);

	ObjectsManager::Initialize();
	ObjectsManager::AddGameObject(move(player));
	ObjectsManager::AddGameObject(move(startMob));


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
		if (keys[DIK_W]) { playerPtr->MoveUp(); }
		if (keys[DIK_S]) { playerPtr->MoveDown(); }
		if (keys[DIK_A]) { playerPtr->MoveLeft(); }
		if (keys[DIK_D]) { playerPtr->MoveRight(); }
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { playerPtr->Fire(); }

		EnemySporner::SpawnEnemy();
		ObjectsManager::UpdateAll();
		ObjectsManager::CollisionCheckAll();

		ObjectsManager::DrawAll();

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

	ObjectsManager::Finalize();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
