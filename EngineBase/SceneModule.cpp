#include "SceneModule.h"
#include "Application.h"

SceneModule::SceneModule()
:m_NextAvailableId(1)
{
}

//Data drive approach - objects ask modules for initialization
void SceneModule::SignalQueuedObjects()
{
	for (auto obj : m_GameObjectsJustAdded)
	{
		obj->SignalInitialization();
	}
}

void SceneModule::Update()
{
	auto& gameObjects = m_RunningScene.m_GameObjects;

	//Add to the pool and call Awake() on each component
	//Itterate over a separate list so that Objects can be instantiated in the Awake function
	auto justAdded = std::vector<GameObject*>(m_GameObjectsJustAdded);
	m_GameObjectsJustAdded.clear();
	for (auto obj : justAdded)
	{
		gameObjects.push_back(std::unique_ptr<GameObject>(obj));
		obj->Initialize();
	}

	//Update all game objects (dynamic componenets)
	for (auto& gObject : gameObjects )
		gObject->Update();
}

void SceneModule::LateUpdate()
{
	auto& gameObjects = m_RunningScene.m_GameObjects;

	//Late update all game objects (dynamic componenets)
	for (auto& gObject : gameObjects)
		gObject->LateUpdate();

	//Remove objects from the pool
	DestroyRemovedObjects();
	
	RemoveFromPool();

	m_GameObjectsJustRemoved.clear();
}

void SceneModule::DestroyRemovedObjects()
{
	for (auto obj : m_GameObjectsJustRemoved)
	{
		obj->Removed();
	}
}


void SceneModule::RegisterGameObject(GameObject* gObject)
{
	m_GameObjectsJustAdded.push_back(gObject);
}

void SceneModule::UnregisterGameObject(GameObject* gObject)
{
	m_GameObjectsJustRemoved.push_back(gObject);
}

std::vector<std::unique_ptr<GameObject>> const& SceneModule::GetSceneGameObjects()
{
	return Application::GetSceneModule().m_RunningScene.m_GameObjects;
}

std::vector<GameObject*> const& SceneModule::GetDestroyedObjectsThisFrame()
{
	return Application::GetSceneModule().m_GameObjectsJustRemoved;
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
	for (auto obj : m_GameObjectsJustRemoved)
	{
		auto found = std::find_if(gObjects.begin(), gObjects.end(),
			[&obj](std::unique_ptr<GameObject>const& item) { return item.get() == obj; });
		
		m_DestroyedIds.push(obj->GetId());

		if (found != gObjects.end())
			gObjects.erase(found);
	}
}