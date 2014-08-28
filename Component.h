#ifndef COMPONENT_H
#define COMPONENT_H

#include "WatchPtr.h"

#include <string>

class GameObject;

class Component
	: Watchable
{
protected:

	//The GameObject which owns the component
	GameObject* m_GameObject;
public:
	virtual ~Component();
	Component();

	inline GameObject* GetGameObject() { return m_GameObject; };

	virtual void OnSignalingInitiazation();
	virtual void OnDestruction();
	virtual void SetOwner(GameObject* obj);

	virtual void Awake();
	virtual void Start();

	std::string const& GetTag() const;
	std::string const& GetName() const;
	int GetLayer() const;
};
#endif