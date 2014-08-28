#ifndef SCENE_MODULE_H
#define SCENE_MODULE_H
#include "Scene.h"

class SceneModule
{
public:
	SceneModule();

	void SignalQueuedObjects();
	void Update();
	void LateUpdate();
	void DestroyRemovedObjects();

	void RegisterGameObject(GameObject* gObject);
	void UnregisterGameObject(GameObject* gObject);

	static std::vector<std::unique_ptr<GameObject>> const& GetSceneGameObjects();
	static std::vector<GameObject*> const& GetDestroyedObjectsThisFrame();
	static unsigned int GetUniqueId();

	void LoadScene(const std::string& sceneName);
private:
	void RemoveFromPool();

	Scene						m_RunningScene;

	std::vector<GameObject*>	m_GameObjectsJustAdded;
	std::vector<GameObject*>	m_GameObjectsJustRemoved;

	//Id management
	std::queue<unsigned int>    m_DestroyedIds;
	unsigned int				m_NextAvailableId;
};

#endif