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
#include <random>
#include <time.h>

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
	srand(static_cast<unsigned int>(time(nullptr)));

	NoviceUtility::kWhiteGraphHandle = Novice::LoadTexture("white1x1.png");


	PlayerConfig playerConfig{};
	playerConfig.tag = ObjectTag::Player;
	playerConfig.sizeHalf = Vector2(16.0f, 16.0f);
	playerConfig.hp = 10;
	playerConfig.color = 0x00aaaaff;
	playerConfig.speed = 10.0f;
	playerConfig.shotInterval = 0.5f;
	playerConfig.isActive = true;
	playerConfig.centerPosition = Vector2(NoviceUtility::kWindowWidth / 2, NoviceUtility::kWindowHeight - 100);
	unique_ptr<Player> player = make_unique<Player>(playerConfig);

	BaseMobConfig startMobConfig{};
	startMobConfig.tag = ObjectTag::Enemy;
	startMobConfig.sizeHalf = Vector2(16.0f, 16.0f);
	startMobConfig.hp = 1;
	startMobConfig.color = 0xaaaa00ff;
	startMobConfig.centerPosition = Vector2(NoviceUtility::kWindowWidth / 2, 100);
	startMobConfig.speed = 0.0f;
	startMobConfig.isActive = true;
	unique_ptr<BaseMob> startMob = make_unique<BaseMob>(startMobConfig);

	Player* playerPtr = player.get();
	BaseMob::SetTargetPtr(playerPtr);

	BaseMobConfig baseMobConfig{};
	baseMobConfig.tag = ObjectTag::Enemy;
	baseMobConfig.sizeHalf = Vector2(16.0f, 16.0f);
	baseMobConfig.hp = 10;
	baseMobConfig.color = 0xaaaa00ff;

	BulletConfig bulletConfig{};
	bulletConfig.isActive = true;
	bulletConfig.isDangerous = true;
	bulletConfig.centerPosition = player->GetPosition();
	bulletConfig.color = 0x0008888ff;
	bulletConfig.sizeHalf = Vector2(5.0f, 5.0f);
	bulletConfig.speed = 10.0f;
	bulletConfig.tag = ObjectTag::PlayerBullet;
	bulletConfig.moveDir = Vector2(0.0f, -1.0f);
	bulletConfig.damage = 1;
	playerPtr->SetBuletConfig(bulletConfig);

	ObjectsManager::Initialize();
	ObjectsManager::AddGameObject(move(player));
	ObjectsManager::AddGameObject(move(startMob));

	int waveCount = 0;



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
		if (keys[DIK_SPACE]) { playerPtr->Fire(); }
		ObjectsManager::UpdateAll();
		ObjectsManager::CollisionCheckAll();

		if (ObjectsManager::IsEnemyAllDead()) {
			waveCount++;

 			baseMobConfig.hp = waveCount * waveCount;
			baseMobConfig.color = 0xffaa00ff -(waveCount * 0x00110000);
			baseMobConfig.sizeHalf = Vector2(16.0f + waveCount * 2.0f, 16.0f + waveCount * 2.0f);
			baseMobConfig.speed = 0.3f + waveCount * 0.02f;

			EnemySporner::SpawnEnemy(baseMobConfig);
		}

		ObjectsManager::DrawAll();
		ObjectsManager::DebugDraw();

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
