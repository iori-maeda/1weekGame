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

void EnemySporner::SpawnEnemy(const BaseMobConfig& config)
{
	if (!ObjectsManager::IsEnemyAllDead()) { return; }

	sEnemySpawnCount++;
	for (int i = 0; i < sEnemySpawnCount; i++)
	{
		float randomAngle = rand() % 361 * (std::numbers::pi_v<float> / 180.0f);
		Vector2 screenSize = Vector2(static_cast<float>(NoviceUtility::kWindowWidth), static_cast<float>(NoviceUtility::kWindowHeight));
		const float kBaseSpawnPositionLength = screenSize.Length() / 2.0f;

		Vector2 spanwPosition = Vector2(cosf(randomAngle), sinf(randomAngle)) * kBaseSpawnPositionLength + NoviceUtility::kCenterScreen;

		BaseMobConfig spawnConfig = config;
		spawnConfig.tag = ObjectTag::Enemy;
		spawnConfig.centerPosition = spanwPosition;
		spawnConfig.moveDir = Vector2::Normalize(NoviceUtility::kCenterScreen - spanwPosition);

		unique_ptr<BaseMob> mob = make_unique<BaseMob>(spawnConfig);

		ObjectsManager::AddGameObject(move(mob));
	}
}