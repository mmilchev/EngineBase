#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "QueuedVector.h"

class RendererComponent;
namespace sf
{
	class RenderTarget;
}

class CameraComponent
	:public Component
{
public:
	CameraComponent();

	void SetViewport(float x, float y, float width, float height);
	void SetOrthoSize(float size);
	void OnSignalingInitiazation() override;
	void OnDestruction() override;

	void SetLayerMask(int mask);

	void Render(QueuedVector<RendererComponent*> const& gObjects);

	void Zoom(float factor);

	sf::Vector2f ScreenToWorldSpace(sf::Vector2i const& pos) const;

	void Awake() override;

	void SetRenderTarget(sf::RenderTarget* target);

	inline bool ShouldRenderLayer(int layer) { return (layer & m_LayerMask) == layer; };
private:
	void AdjustScreenSize();
	void ApplyView();

	sf::View m_View;
	float m_OrthoSize;
	int	m_LayerMask;
	
	sf::RenderTarget* m_RenderTarget;
};

#endif