#ifndef RENDERER_COMPONENT_H
#define RENDERER_COMPONENT_H

#include "Component.h"
#include <SFML/Graphics.hpp>

class TransformComponent;
namespace sf
{
	class RenderTarget;
}

class RendererComponent
	: public Component
{
public:
	void OnSignalingInitiazation() override;
	void OnDestruction() override;
	
	void SetOrder(int order);
	inline int GetOrder() const { return m_Order; }

	virtual void Render(sf::RenderTarget& renderTarget) = 0;
	
protected:
	RendererComponent();

	void ApplyTransformation(sf::Transformable& transformable);
	//Passing the argument for optimization
	virtual sf::Vector2f GetScale(TransformComponent const* transform) const = 0;

	int m_Order;
};

#endif