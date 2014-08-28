#include "RendererComponent.h"
#include "Application.h"

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