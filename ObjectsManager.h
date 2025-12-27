#pragma once
#include "GameObject.h"
#include "BaseItem.h"
#include <memory>
#include <list>

class ObjectsManager
{
public:
	static void Initialize();
	static void Finalize();
	static void UpdateAll();
	static void DrawAll();
	static void CollisionCheckAll();
	static void AddGameObject(std::unique_ptr<GameObject> obj);
	static void CreateItem(const Vector2 &position, ItemType type = ItemType::None);

	static void DebugDraw();

public:
	static bool IsEnemyAllDead();

private:
	ObjectsManager() = default;



private:

	static ObjectsManager *mInstance;
	static std::list<std::unique_ptr<GameObject>> mObjects;
};

