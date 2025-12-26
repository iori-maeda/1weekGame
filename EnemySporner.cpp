#include "EnemySporner.h"

#include <memory>
#include <random>
#include <numbers>
#include <cmath>

#include "BaseMob.h"
#include "ObjectsManager.h"
#include "NoviceUtility.h"
#include "Vector2.h"

using namespace std;


int EnemySporner::sEnemySpawnCount = 1;

void EnemySporner::SpawnEnemy()
{
	if (!ObjectsManager::IsEnemyAllDead()) { return; }

	sEnemySpawnCount++;
	for (int i = 0; i < sEnemySpawnCount; i++)
	{
		float randomAngle = rand() % 360 * (std::numbers::pi_v<float> / 180.0f);
		const float kBaseSpawnPositionLength = Vector2(static_cast<float>(NoviceUtility::kWindowWidth), static_cast<float>(NoviceUtility::kWindowHeight)).Length() * 1.1f;

		Vector2 spanwPosition = Vector2(cosf(randomAngle), sinf(randomAngle)) * kBaseSpawnPositionLength + NoviceUtility::kCenterScreen;

		BaseMobConfig config{};
		config.tag = ObjectTag::Enemy;
		config.centerPosition = spanwPosition;
		config.sizeHalf = Vector2(16.0f, 16.0f);
		config.hp = sEnemySpawnCount * sEnemySpawnCount;
		config.moveDir = Vector2::Normalize(NoviceUtility::kCenterScreen - spanwPosition);
		config.color = 0xaaaa00ff;

		unique_ptr<BaseMob> mob = make_unique<BaseMob>(config);

		ObjectsManager::AddGameObject(move(mob));
	}
}
