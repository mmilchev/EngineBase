#ifndef SCENE_MODULE_H
#define SCENE_MODULE_H

#include "QueuedVector.h"
#include "GameObject.h"

class SceneModule
{
public:
	SceneModule();

	void ProcessQueuedObjects();

	void Update();
	void LateUpdate();
	void DestroyRemovedObjects();

	void RegisterGameObject(GameObject* gObject);
	void UnregisterGameObject(GameObject* gObject);

	void RemoveObjectForSceneChange();
	void RemoveAllObjects();

	static std::vector<std::unique_ptr<GameObject>> const& GetSceneGameObjects();
	static std::vector<GameObject*> const& GetDestroyedObjectsThisFrame();
	static unsigned int GetUniqueId();
private:
	void RemoveFromPool();

	std::vector<std::unique_ptr<GameObject>> m_GameObjects;

	QueuedVector<GameObject*>	m_GameObjectsJustAdded;
	QueuedVector<GameObject*>	m_GameObjectsJustRemoved;

	//Id management
	std::queue<unsigned int>    m_DestroyedIds;
	unsigned int				m_NextAvailableId;
};

#endif