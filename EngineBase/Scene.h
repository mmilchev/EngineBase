#ifndef SCENE_H
#define SCENE_H
#include "QueuedVectorPtr.h"
#include "GameObject.h"

class Scene
{
public:
	Scene();

	void CreateDefaultCamera();

	std::vector<std::unique_ptr<GameObject>> m_GameObjects;

	///Extracts naked pointers from the smart pointers
	///Beware: Can be slow
	std::vector<GameObject*> GetGameObjects();
};

#endif
