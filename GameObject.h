#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include "Component.h"
#include "WatchPtr.h"

class TransformComponent;
class DynamicBehaviour;
struct CollisionData;

class GameObject
	: public Watchable
{
public:
	GameObject();
	void AddComponent(Component* comp);
	
	void SignalInitialization();
	void Initialize();
	void Removed();

	void Update();
	void LateUpdate();

	//Collision callbacks
	void OnCollisionEnter(CollisionData& collision);
	void OnCollisionExit(CollisionData& collision);

	//Input interaction
	void OnClicked();
	void OnMouseEnter();
	void OnMouseLeave();

	TransformComponent* Transform();
	void SetParent(GameObject* parent);
	std::vector<GameObject*> GetChildren();
	void GetChildren(std::vector<GameObject*>& vec);
	std::vector<GameObject*> GetChildrenWithTag(std::string const& tag);
	GameObject* GetChildWithTag(std::string const& tag);
	GameObject* GetChildWithName(std::string const& name);

	template<class CompType>
	CompType* GetComponent();
	template<class CompType>
	std::vector<CompType*> GetComponents();

	inline unsigned int GetId() const { return m_Id; }
	void SetId(unsigned int id);

	void PushDynamicBehaviour(DynamicBehaviour* behaviour);
	
	inline bool IsDynamic() const { return m_DynamicBehaviours.size() > 0; }
	inline bool IsDestroyed() const { return m_Destroyed; }

	inline void SetTag(const std::string& tag) { m_Tag = tag; }
	inline void SetName(const std::string& name) { m_Name = name; }
	inline void SetLayer(int layer) { m_Layer = layer; };
	inline std::string const& GetName() const { return m_Name; }
	inline std::string const& GetTag()	const { return m_Tag; }
	inline int GetLayer() const { return m_Layer; }

	static GameObject* FindByName(const std::string& name);
	static GameObject* FindByTag(const std::string& tag);
	static std::vector<GameObject*> FindObjectsByTag(const std::string& tag);

	static void Instantiate(GameObject* gObject);
	static void Destroy(GameObject* gObject);
private:
	unsigned int m_Id;
	bool m_Instantiated;
	bool m_Destroyed;

	std::string	m_Name;
	std::string	m_Tag;
	int			m_Layer;

	std::vector<std::unique_ptr<Component>> m_Components;
	std::vector<Component*>					m_ComponentInitQueue;
	std::vector<DynamicBehaviour*>			m_DynamicBehaviours;
};

template <class CompType>
CompType* GameObject::GetComponent()
{
	for (auto& comp : m_Components)
	{
		auto cast = dynamic_cast<CompType*>(comp.get());
		if (cast != nullptr)
			return cast;
	}
	return nullptr;
}

template <class CompType>
std::vector<CompType*> GameObject::GetComponents()
{
	std::vector<CompType*> comps;
	for (auto& comp : m_Components)
	{
		auto cast = dynamic_cast<CompType*>(comp.get());
		if (cast != nullptr)
			comps.push_back(cast);
	}
	return comps;
}
#endif