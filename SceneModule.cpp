#include "SceneModule.h"
#include "Application.h"

SceneModule::SceneModule()
:m_NextAvailableId(1)
{
}

//Data driven approach - objects ask modules for initialization
void SceneModule::ProcessQueuedObjects()
{
	//Remove deleted objects
	m_GameObjectsJustRemoved.ProcessQueued();

	//Remove objects from the pool
	DestroyRemovedObjects();

	Application::ProcessQeuedObjectsInModules();

	RemoveFromPool();

	m_GameObjectsJustRemoved.Clear();

	//Init added objects
	m_GameObjectsJustAdded.ProcessQueued();

	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		m_GameObjectsJustAdded[i]->SignalInitialization();
	}

	//Add to the pool and call Awake() on each component
	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		m_GameObjects.push_back(std::unique_ptr<GameObject>(m_GameObjectsJustAdded[i]));
	}
	for (int i = 0; i < m_GameObjectsJustAdded.Size(); ++i)
	{
		m_GameObjectsJustAdded[i]->Initialize();
	}

	Application::ProcessQeuedObjectsInModules();

	m_GameObjectsJustAdded.Clear();
}


void SceneModule::Update()
{
	//Update all game objects (dynamic componenets)
	for (auto& gObject : m_GameObjects)
		gObject->Update();
}

void SceneModule::LateUpdate()
{
	//Late update all game objects (dynamic componenets)
	for (auto& gObject : m_GameObjects)
		gObject->LateUpdate();
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
	return Application::GetSceneModule().m_GameObjects;
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

void SceneModule::RemoveFromPool()
{
	for (int i = 0; i < m_GameObjectsJustRemoved.Size(); ++i)
	{
		auto obj = m_GameObjectsJustRemoved[i];

		auto found = std::find_if(m_GameObjects.begin(), m_GameObjects.end(),
			[&obj](std::unique_ptr<GameObject>const& item) { return item.get() == obj; });

		//If the object is not already in the pool, it has to be in the Add queue
		if (found != m_GameObjects.end())
		{
			m_DestroyedIds.push(obj->GetId());
			m_GameObjects.erase(found);
		}
		else
		{
			//Delete object if it isn't already in the main object pool
			//Also they were never assigned an ID
			m_GameObjectsJustAdded.RemoveAddedInstance(obj);
			delete obj;
		}
	}
}

void SceneModule::RemoveObjectForSceneChange()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); ++i)
	{
		auto gObject = m_GameObjects[i].get();
		if (gObject->ShouldDestroyOnSceneChange())
			GameObject::Destroy(gObject);
	}
		
}

void SceneModule::RemoveAllObjects()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); ++i)
	{
		GameObject::Destroy(m_GameObjects[i].get());
	}
}
