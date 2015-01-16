#ifndef BOX_INTERACTION_COMPONENT_H
#define BOX_INTERACTION_COMPONENT_H

#include "IShaped.h"
#include "Component.h"

class BoxInteractionComponent
	: public Component, public IShaped
{
public:
	BoxInteractionComponent(float width, float height);

	virtual bool Contains(sf::Vector2f const& pos) override;

private:
	float m_Width, m_Height;
};

#endif