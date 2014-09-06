#pragma once
#include "Tween.h"
#include <SFML/System/Vector2.hpp>

class Tween2
{
public:
	void Set(sf::Vector2f const& from, sf::Vector2f const& to, float time, Tween::TweenType type = Tween::TweenType::Linear);
	void Update(float dt);
	
	inline sf::Vector2f const& GetValue() const { return m_Value; }
	inline bool Done() const { return m_TweenX.Done() && m_TweenY.Done(); }

private:
	sf::Vector2f m_Value;
	Tween m_TweenX, m_TweenY;
};