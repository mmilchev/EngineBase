#include "Scene.h"
#include "GameObject.h"
#include "CameraComponent.h"

Scene::Scene()
{
}

void Scene::CreateDefaultCamera()
{
	auto cameraObject = new GameObject();
	cameraObject->SetName("Camera");
	cameraObject->SetTag("Camera");
	cameraObject->AddComponent(new CameraComponent());
	GameObject::Instantiate(cameraObject);
}

std::vector<GameObject*> Scene::GetGameObjects()
{
	std::vector<GameObject*> objects;
	for (auto const& obj: m_GameObjects)
	{
		objects.push_back(obj.get());
	}
	return objects;
}