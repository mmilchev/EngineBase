#include "TransformComponent.h"

TransformComponent::TransformComponent()
:m_Parent(nullptr)
{
}

sf::Vector2f TransformComponent::Scale() const
{
	return (m_Parent == nullptr) ? (m_LocalTransform.m_Scale) : (m_Parent->Scale() + m_LocalTransform.m_Scale);
}

sf::Vector2f TransformComponent::Position() const
{
	return GetTransform().m_Transform.transformPoint(0, 0);
}

float TransformComponent::Rotation() const
{
	return (m_Parent == nullptr) ? (m_LocalTransform.m_Rotation) : (m_Parent->Rotation() + m_LocalTransform.m_Rotation);
}

void TransformComponent::SetPosition(sf::Vector2f const& newPosition)
{
	m_LocalTransform.m_Position = (m_Parent == nullptr) ? (newPosition) : (newPosition - m_Parent->Position());
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::SetScale(sf::Vector2f const& newScale)
{
	m_LocalTransform.m_Scale = (m_Parent == nullptr) ? (newScale) : (newScale - m_Parent->Scale());
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::SetRotation(float newRotation)
{
	m_LocalTransform.m_Rotation = (m_Parent == nullptr) ? (newRotation) : (newRotation - m_Parent->Rotation());
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::SetLocalPosition(sf::Vector2f const& newPosition)
{
	m_LocalTransform.m_Position = newPosition;
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::SetLocalScale(sf::Vector2f const& newScale)
{
	m_LocalTransform.m_Scale = newScale;
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::SetLocalRotation(float newRotation)
{
	m_LocalTransform.m_Rotation = newRotation;
	m_LocalTransform.CalculateMatrix();
}

void TransformComponent::Translate(sf::Vector2f const& delta)
{
	SetPosition(Position() + delta);
}

Transform2D TransformComponent::GetTransform() const
{
	if (m_Parent != nullptr)
	{
		Transform2D transform = m_Parent->GetTransform();
		transform.m_Transform.combine(m_LocalTransform.m_Transform);
		return transform;
	}

	return m_LocalTransform;
}

void TransformComponent::AddChild(TransformComponent* component)
{
	m_Children.push_back(component);
}

void TransformComponent::RemoveChild(TransformComponent const* conponent)
{
	auto result = std::find(m_Children.begin(), m_Children.end(), conponent);
	if (result != m_Children.end())
		m_Children.erase(result);
}

void TransformComponent::SetParent(TransformComponent* component)
{
	if (m_Parent != nullptr)
		m_Parent->RemoveChild(this);

	m_Parent = component;

	if (m_Parent != nullptr)
	{
		m_Parent->AddChild(this);
		//Set the new coordinates
		SetPosition(m_LocalTransform.m_Position);
		SetScale(m_LocalTransform.m_Scale);
		SetRotation(m_LocalTransform.m_Rotation);
	}
}

void TransformComponent::GetChildren(std::vector<TransformComponent*>& children)
{
	//Use recursion to get all the children in the tree
	for (auto child : m_Children)
	{
		children.push_back(child);
		child->GetChildren(children);
	}
}

void TransformComponent::OnDestruction()
{
	for (unsigned int i = 0; i < m_Children.size(); ++i)
	{
		m_Children[i]->SetParent(nullptr);
	}

	if (m_Parent != nullptr)
		m_Parent->RemoveChild(this);

	m_Parent = nullptr;
}
