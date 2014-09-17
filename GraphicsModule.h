#ifndef GRAPHICS_MODULE_H
#define GRAPHICS_MODULE_H
#include "QueuedVector.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class RendererComponent;
class CameraComponent;

class GraphicsModule
{
public:
	GraphicsModule();

	void Initialize(const sf::Vector2u& targetRes);

	void ProcessQueuedObjects();

	void RegisterRenderer(RendererComponent* comp);
	void UnregisterRenderer(RendererComponent* comp);

	void RegisterCamera(CameraComponent* comp);
	void UnregisterCamera(CameraComponent* comp);

	void CheckAndSortRenderers();
	void SignalRenderersResorting();

	void Render();

	sf::RenderTexture* GetRenderTexture();
	sf::Sprite const& GetSprite() const;
	sf::Vector2u const& GetTargetResolution() const;
	std::vector<CameraComponent*> const& GetCameras() const;
private:
	bool m_ShouldSortRenderers;
	QueuedVector<RendererComponent*> m_Renderers;
	QueuedVector<CameraComponent*> m_Cameras;

	sf::Sprite m_RenderSprite;
	sf::RenderTexture m_RenderTexture;

	sf::Vector2u m_TargetResolution;
};

#endif