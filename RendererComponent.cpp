#include "RendererComponent.h"
#include "Application.h"
#include "GameObject.h"
#include "TransformComponent.h"

void RendererComponent::OnSignalingInitiazation()
{
	Application::GetGraphicsModule().RegisterRenderer(this);
}

void RendererComponent::OnDestruction()
{
	Application::GetGraphicsModule().UnregisterRenderer(this);
}

void RendererComponent::SetOrder(int order)
{
	int old = m_Order;
	m_Order = order;
	if (old != order)
	{
		Application::GetGraphicsModule().SignalRenderersResorting();
	}
}

RendererComponent::RendererComponent()
:m_Order(0)
{
}

void RendererComponent::ApplyTransformation(sf::Transformable& transformable)
{
	auto transform = m_GameObject->Transform();
	transformable.setPosition(transform->Position());
	transformable.setRotation(transform->Rotation());
	transformable.setScale(GetScale(transform));
}