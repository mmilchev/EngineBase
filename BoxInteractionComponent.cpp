#include "BoxInteractionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"



bool BoxInteractionComponent::Contains(sf::Vector2f const& pos)
{
	auto localPos = m_GameObject->Transform()->Position();
	int hW = m_Width / 2;
	int hH = m_Height / 2;
	return pos.x >= localPos.x - hW
		&& pos.x <= localPos.x + hW
		&& pos.y >= localPos.y - hH
		&& pos.y <= localPos.y + hH;
}

BoxInteractionComponent::BoxInteractionComponent(int width, int height)
	:m_Width(width), m_Height(height)
{
}
