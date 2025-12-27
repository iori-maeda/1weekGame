#pragma once
#include "BaseMob.h"

class EnemySporner
{
public:
	static int sEnemySpawnCount;

	static void SpawnEnemy(const BaseMobConfig& config);
};

