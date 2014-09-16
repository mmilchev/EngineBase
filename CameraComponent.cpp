#include "CameraComponent.h"
#include "Application.h"
#include "RendererComponent.h"
#include "TransformComponent.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

CameraComponent::CameraComponent()
	:m_OrthoSize(5)
{
	m_LayerMask = ~0; //All layers
	SetViewport(0, 0, 1, 1);
}

void CameraComponent::SetViewport(float x, float y, float width, float height)
{
	m_View.setViewport(sf::FloatRect(x, y, width, height));
}

void CameraComponent::SetOrthoSize(float size)
{
	m_OrthoSize = size;
}

void CameraComponent::OnSignalingInitiazation()
{
	Application::GetGraphicsModule().RegisterCamera(this);
}

void CameraComponent::OnDestruction()
{
	Application::GetGraphicsModule().UnregisterCamera(this);
}

void CameraComponent::SetLayerMask(int mask)
{
	m_LayerMask = mask;
}

void CameraComponent::Render(QueuedVector<RendererComponent*> const& renderers)
{
	ApplyView();
	auto objSize = renderers.Size();
	for (int i = 0; i < objSize; ++i)
	{
		auto renderer = renderers[i];
		if (ShouldRenderLayer(renderer->GetLayer()))
		{
			renderer->Render(*m_RenderTarget);
		}
	}
}

void CameraComponent::Zoom(float factor)
{
	m_View.zoom(factor);
	ApplyView();
}

sf::Vector2f CameraComponent::ScreenToWorldSpace(sf::Vector2i const& pos) const
{
	return m_RenderTarget->mapPixelToCoords(pos, m_View);
}

void CameraComponent::Awake()
{
	SetRenderTarget(Application::GetDefaultRenderTarget());
	AdjustScreenSize();
}

void CameraComponent::SetRenderTarget(sf::RenderTarget* target)
{
	m_RenderTarget = target;
	ApplyView();
}

void CameraComponent::AdjustScreenSize()
{
	auto& res = Application::GetGraphicsModule().GetTargetResolution();
	auto size = ToVecf(res);
	m_View.setSize(size.x, size.y);
	auto position = m_GameObject->Transform()->Position();
	m_View.setCenter(position.x, position.y);
	ApplyView();
}

void CameraComponent::ApplyView()
{
	m_View.setCenter(m_GameObject->Transform()->Position());
	if (m_RenderTarget != nullptr)
	{
		m_RenderTarget->setView(m_View);
	}
}