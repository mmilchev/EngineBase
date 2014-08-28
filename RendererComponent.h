#ifndef RENDERER_COMPONENT_H
#define RENDERER_COMPONENT_H

#include "Component.h"

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

	int m_Order;
};

#endif