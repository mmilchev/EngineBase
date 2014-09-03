#include "GameObject.h"
#include "TransformComponent.h"
#include "DynamicBehaviour.h"
#include "Application.h"

//Private constructor 
GameObject::GameObject()
:m_Name(""), m_Tag("Default"), m_Layer(0), m_Instantiated(false), m_Destroyed(false), m_Id(0)
{
	//Every gameObject has a transform
	AddComponent(new TransformComponent());
}

void GameObject::AddComponent(Component* comp)
{
	m_Components.push_back(std::unique_ptr<Component>(comp));
	m_ComponentInitQueue.push_back(comp);
	comp->SetOwner(this);
}

//Calling Awake on all components before doing any updates
void GameObject::SignalInitialization()
{
	for (auto comp : m_ComponentInitQueue)
		comp->OnSignalingInitiazation();
}

void GameObject::Initialize()
{
	SetId(SceneModule::GetUniqueId());

	for (auto comp : m_ComponentInitQueue)
		comp->Awake();
}

void GameObject::Removed()
{
	for (auto& comp : m_Components)
	{
		comp->OnDestruction();
	}
}

void GameObject::Update()
{
	//Calling Start on all components after calling Awake and before any Update methods are called
	if (m_ComponentInitQueue.size() > 0)
	{
		for (auto comp : m_ComponentInitQueue)
			comp->Start();
		m_ComponentInitQueue.clear();
	}

	for (auto dynamicBehaviour : m_DynamicBehaviours)
	{
		dynamicBehaviour->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
	{
		dynamicBehaviour->LateUpdate();
	}
}

void GameObject::OnCollisionEnter(CollisionData& collision)
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
		dynamicBehaviour->OnCollisionEnter(collision);
}

void GameObject::OnCollisionExit(CollisionData& collision)
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
		dynamicBehaviour->OnCollisionExit(collision);
}

void GameObject::OnClicked()
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
		dynamicBehaviour->OnClicked();
}

void GameObject::OnMouseEnter()
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
		dynamicBehaviour->OnMouseEnter();
}

void GameObject::OnMouseLeave()
{
	for (auto dynamicBehaviour : m_DynamicBehaviours)
		dynamicBehaviour->OnMouseLeave();
}

void GameObject::SetId(unsigned id)
{
	//Can be set only once
	assert(m_Id == 0);

	m_Id = id;
}

void GameObject::PushDynamicBehaviour(DynamicBehaviour* behaviour)
{
	m_DynamicBehaviours.push_back(behaviour);
}

GameObject* GameObject::FindByName(std::string const& name)
{
	auto& gObjects = SceneModule::GetSceneGameObjects();

	for (auto const& gObject : gObjects)
	{
		if (gObject->GetName() == name)
		{
			return gObject.get();
		}
	}

	return nullptr;
}

GameObject* GameObject::FindByTag(std::string const& tag)
{
	auto& gObjects = SceneModule::GetSceneGameObjects();
	
	for (auto const& gObject : gObjects)
	{
		if (gObject->GetTag() == tag)
		{
			return gObject.get();
		}
	}

	return nullptr;
}

std::vector<GameObject*> GameObject::FindObjectsByTag(std::string const& tag)
{
	std::vector<GameObject*> taggedObjects;

	auto& gObjects = SceneModule::GetSceneGameObjects();
	for (auto const& obj : gObjects)
	{
		if (obj->m_Tag == tag)
			taggedObjects.push_back(obj.get());
	}

	return taggedObjects;
}

void GameObject::Instantiate(GameObject* gObject)
{
	if (gObject->m_Instantiated)
		return;

	Application::GetSceneModule().RegisterGameObject(gObject);

	auto children = gObject->GetChildren();
	for (auto child : children)
	{
		Instantiate(child);
	}

	gObject->m_Instantiated = true;
}

void GameObject::Destroy(GameObject* gObject)
{
	if (!gObject->m_Instantiated ||
		gObject->m_Destroyed)
		return;

	Application::GetSceneModule().UnregisterGameObject(gObject);

	auto children = gObject->GetChildren();
	for (auto child : children)
	{
		Destroy(child);
	}

	gObject->m_Destroyed = true;
}

TransformComponent* GameObject::Transform()
{
	return GetComponent<TransformComponent>();
}

void GameObject::SetParent(GameObject* parent)
{
	Transform()->SetParent(parent->Transform());
}

std::vector<GameObject*> GameObject::GetChildren()
{
	std::vector<GameObject*> children;
	GetChildren(children);

	return children;
}

void GameObject::GetChildren(std::vector<GameObject*>& vec)
{
	std::vector<TransformComponent*> transChildren;
	Transform()->GetChildren(transChildren);

	for (const auto child : transChildren)
	{
		auto gObject = child->GetGameObject();
		vec.push_back(gObject);
	}
}

std::vector<GameObject*> GameObject::GetChildrenWithTag(std::string const& tag)
{
	std::vector<GameObject*> children;

	std::vector<TransformComponent*> transChildren;
	Transform()->GetChildren(transChildren);
	
	for (const auto child : transChildren)
	{
		auto gObject = child->GetGameObject();
		if (gObject->GetTag() == tag)
			children.push_back(gObject);
	}

	return children;
}

GameObject* GameObject::GetChildWithTag(std::string const& tag)
{
	std::vector<TransformComponent*> transChildren;
	Transform()->GetChildren(transChildren);

	for (const auto child : transChildren)
	{
		auto gObject = child->GetGameObject();
		if (gObject->GetTag() == tag)
			return gObject;
	}

	return nullptr;
}

GameObject* GameObject::GetChildWithName(std::string const& name)
{
	std::vector<TransformComponent*> transChildren;
	Transform()->GetChildren(transChildren);

	for (const auto child : transChildren)
	{
		auto gObject = child->GetGameObject();
		if (gObject->GetName() == name)
			return gObject;
	}

	return nullptr;
}