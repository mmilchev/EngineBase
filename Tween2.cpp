#include "Tween2.h"

void Tween2::Set(sf::Vector2f const& from, sf::Vector2f const& to, float time, Tween::TweenType type)
{
	m_TweenX.Set(from.x, to.x, time, type);
	m_TweenY.Set(from.y, to.y, time, type);
}

void Tween2::Update(float dt)
{
	m_TweenX.Update(dt);
	m_TweenY.Update(dt);

	m_Value.x = m_TweenX.GetValue();
	m_Value.y = m_TweenY.GetValue();
}