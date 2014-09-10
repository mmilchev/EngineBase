#include "GraphicsModule.h"
#include "RendererComponent.h"
#include "CameraComponent.h"

GraphicsModule::GraphicsModule()
:m_ShouldSortRenderers(true)
{
}

void GraphicsModule::Initialize(sf::Vector2u const& targetRes)
{
	m_TargetResolution = targetRes;

	m_RenderTexture.create(m_TargetResolution.x, m_TargetResolution.y, true);
	m_RenderTexture.setSmooth(true);
	m_RenderSprite.setTexture(m_RenderTexture.getTexture());
}

void GraphicsModule::RegisterRenderer(RendererComponent* comp)
{
	m_Renderers.Add(comp);
	SignalRenderersResorting();
}

void GraphicsModule::UnregisterRenderer(RendererComponent* comp)
{
	m_Renderers.Remove(comp);
}

void GraphicsModule::RegisterCamera(CameraComponent* comp)
{
	m_Cameras.Add(comp);
}

void GraphicsModule::UnregisterCamera(CameraComponent* comp)
{
	m_Cameras.Remove(comp);
}

void GraphicsModule::CheckAndSortRenderers()
{
	if (m_ShouldSortRenderers)
	{
		m_Renderers.Sort(
			[](RendererComponent const* lhs, RendererComponent const* rhs) { return lhs->GetOrder() < rhs->GetOrder(); });

		m_ShouldSortRenderers = false;
	}
}

void GraphicsModule::SignalRenderersResorting()
{
	m_ShouldSortRenderers = true;
}

void GraphicsModule::Render()
{
	m_RenderTexture.clear(); //Clear the backbuffer

	m_Cameras.ProcessQueued();
	m_Renderers.ProcessQueued();

	CheckAndSortRenderers();

	int cameraSize = m_Cameras.Size();
	for (int cameraIndex = 0; cameraIndex < cameraSize; ++cameraIndex)
	{
		m_Cameras[cameraIndex]->Render(m_Renderers);
	}

	m_RenderTexture.display();
}

sf::RenderTexture* GraphicsModule::GetRenderTexture()
{
	return &m_RenderTexture;
}

sf::Sprite const& GraphicsModule::GetSprite() const
{
	return m_RenderSprite;
}

sf::Vector2u const& GraphicsModule::GetTargetResolution() const
{
	return m_TargetResolution;
}

std::vector<CameraComponent*> const& GraphicsModule::GetCameras() const
{
	return m_Cameras.GetRawData();
}