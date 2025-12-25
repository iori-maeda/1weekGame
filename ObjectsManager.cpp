#include "ObjectsManager.h"
#include "Collision.h"
#include "NoviceUtility.h"

ObjectsManager* ObjectsManager::mInstance;
std::list<std::unique_ptr<GameObject>> ObjectsManager::mObjects;

void ObjectsManager::Initialize()
{
	if (mInstance != nullptr) { return; }

	mInstance = new ObjectsManager();
}

void ObjectsManager::Finalize()
{
	if (mInstance == nullptr) { return; }
	mObjects.clear();
	delete mInstance;
	mInstance = nullptr;
}

void ObjectsManager::UpdateAll()
{
	if (mInstance == nullptr) { return; }
	for (auto& obj : mObjects)
	{
		if (!obj->IsActive()) { continue; }
		obj->Update();
	}

	// 不要なものを一括で削除
	std::erase_if(mObjects, [](const std::unique_ptr<GameObject>& o) {return !o->IsActive(); });
}

void ObjectsManager::DrawAll()
{
	if (mInstance == nullptr) { return; }
	for (auto& obj : mObjects)
	{
		if (!obj->IsActive()) { continue; }
		NoviceUtility::DrawSprite(*obj, NoviceUtility::kWhiteGraphHandle);
	}
}

void ObjectsManager::CollisionCheckAll()
{
	if (mInstance == nullptr) { return; }
	for (auto& objA : mObjects)
	{
		if (!objA->IsActive()) { continue; }
		for (auto& objB : mObjects)
		{
			if (!objB->IsActive()) { continue; }
			if (objA == objB) { continue; }
			if (Collision::AABB(*objA, *objB))
			{
				objA->OnCollision(*objB);
			}
		}
	}
}

void ObjectsManager::AddGameObject(std::unique_ptr<GameObject> obj)
{
	if (mInstance == nullptr) { return; }
	mObjects.push_back(std::move(obj));
}