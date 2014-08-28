#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "Transform2D.h"

class TransformComponent
	: public Component
{
public:
	TransformComponent();

	sf::Vector2f Position() const;
	sf::Vector2f Scale() const;
	float Rotation() const ;

	void SetPosition(sf::Vector2f const& newPosition);
	void SetScale(sf::Vector2f const& newScale);
	void SetRotation(float newRotation);

	void SetLocalPosition(sf::Vector2f const& newPosition);
	void SetLocalScale(sf::Vector2f const& newScale);
	void SetLocalRotation(float newRotation);

	void Translate(sf::Vector2f const& delta);

	Transform2D GetTransform() const;
	
	void SetParent(TransformComponent* component);

	void GetChildren(std::vector<TransformComponent*>& children);


	inline sf::Vector2f const& LocalPosition() const { return m_LocalTransform.m_Position; }
	inline sf::Vector2f const& LocalScale() const { return m_LocalTransform.m_Scale; }
	inline float LocalRotation() const { return m_LocalTransform.m_Rotation; }

	inline const TransformComponent* GetParent() const { return m_Parent; };
	inline Transform2D const& GetLocalTransform() const { return m_LocalTransform; }
private:
	void AddChild(TransformComponent* component);
	void RemoveChild(const TransformComponent* conponent);

	Transform2D	m_LocalTransform;

	TransformComponent*					m_Parent;
	std::vector<TransformComponent*>	m_Children;
};

#endif