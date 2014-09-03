#include "SceneModule.h"
#include "Application.h"

SceneModule::SceneModule()
:m_NextAvailableId(1)
{
}

//Data driven approach - objects ask modules for initialization
void SceneModule::SignalQueuedObjects()
{
	m_GameObjectsJustAdded.ProcessQueued();

	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		m_GameObjectsJustAdded[i]->SignalInitialization();
	}
}

void SceneModule::Update()
{
	auto& gameObjects = m_RunningScene.m_GameObjects;

	//Add to the pool and call Awake() on each component
	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		gameObjects.push_back(std::unique_ptr<GameObject>(m_GameObjectsJustAdded[i]));
	}
	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		m_GameObjectsJustAdded[i]->Initialize();
	}
	m_GameObjectsJustAdded.Clear();

	//Update all game objects (dynamic componenets)
	for (auto& gObject : gameObjects)
		gObject->Update();
}

void SceneModule::LateUpdate()
{
	auto& gameObjects = m_RunningScene.m_GameObjects;

	//Late update all game objects (dynamic componenets)
	for (auto& gObject : gameObjects)
		gObject->LateUpdate();

	m_GameObjectsJustRemoved.ProcessQueued();

	//Remove objects from the pool
	DestroyRemovedObjects();

	RemoveFromPool();

	m_GameObjectsJustRemoved.Clear();
}

void SceneModule::DestroyRemovedObjects()
{
	for (int i = 0; i < m_GameObjectsJustRemoved.Size(); ++i)
	{
		m_GameObjectsJustRemoved[i]->Removed();
	}
}

void SceneModule::RegisterGameObject(GameObject* gObject)
{
	m_GameObjectsJustAdded.Add(gObject);
}

void SceneModule::UnregisterGameObject(GameObject* gObject)
{
	m_GameObjectsJustRemoved.Add(gObject);
}

std::vector<std::unique_ptr<GameObject>> const& SceneModule::GetSceneGameObjects()
{
	return Application::GetSceneModule().m_RunningScene.m_GameObjects;
}

unsigned int SceneModule::GetUniqueId()
{
	int id;
	auto& module = Application::GetSceneModule();
	if (module.m_DestroyedIds.size() > 0)
	{
		id = module.m_DestroyedIds.front();
		module.m_DestroyedIds.pop();
	}
	else
	{
		id = module.m_NextAvailableId++;
	}

	return id;
}

void SceneModule::LoadScene(std::string const& sceneName)
{
	//Not loading anything for now
	m_RunningScene.CreateDefaultCamera();
}

void SceneModule::RemoveFromPool()
{
	auto& gObjects = m_RunningScene.m_GameObjects; 
	for (int i = 0; i < m_GameObjectsJustRemoved.Size(); ++i)
	{
		auto obj = m_GameObjectsJustRemoved[i];

		auto found = std::find_if(gObjects.begin(), gObjects.end(),
			[&obj](std::unique_ptr<GameObject>const& item) { return item.get() == obj; });

		m_DestroyedIds.push(obj->GetId());

		if (found != gObjects.end())
			gObjects.erase(found);
	}
}