#ifndef BOX_INTERACTION_COMPONENT_H
#define BOX_INTERACTION_COMPONENT_H

#include "IShaped.h"
#include "Component.h"

class BoxInteractionComponent
	: public Component, public IShaped
{
public:
	BoxInteractionComponent(int width, int height);

	virtual bool Contains(sf::Vector2f const& pos) override;

private:
	int m_Width, m_Height;
};

#endif