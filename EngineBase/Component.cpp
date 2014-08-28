#include "Component.h"
#include "GameObject.h"
#include<assert.h>

Component::Component() :
	m_GameObject(nullptr)
{
}

Component::~Component()
{
}

void Component::OnSignalingInitiazation()
{
}

void Component::OnDestruction()
{
}

void Component::SetOwner(GameObject* obj)
{
	//Shouldn't change owner once set
	assert(m_GameObject == nullptr);
	m_GameObject = obj;
}

void Component::Awake()
{
}

void Component::Start()
{
}

std::string const& Component::GetTag() const
{
	return m_GameObject->GetTag();
}

std::string const& Component::GetName() const
{
	return m_GameObject->GetName();
}

int Component::GetLayer() const
{
	return m_GameObject->GetLayer();
}