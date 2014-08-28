#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <SFML/Graphics.hpp>

struct Transform2D
{
public:
	Transform2D()
		:m_Scale(1, 1), m_Position(0, 0), m_Rotation(0)
	{ }
	sf::Vector2f m_Position;
	sf::Vector2f m_Scale;
	float m_Rotation;

	sf::Transform m_Transform;
	
	void CalculateMatrix()
	{
		m_Transform = sf::Transform::Identity;
		m_Transform.translate(m_Position);
		m_Transform.rotate(m_Rotation);
		m_Transform.scale(m_Scale);
	}

	bool operator==(Transform2D const& other) const
	{
		return m_Position == other.m_Position
			&& m_Scale == other.m_Scale
			&& fabsf(m_Rotation - other.m_Rotation) < 0.00001f;
	}

	bool operator!=(Transform2D const& other) const
	{
		return !(*this == other);
	}
};

#endif
