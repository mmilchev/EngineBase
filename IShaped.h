#ifndef ISHAPED_COMPONENT_H
#define ISHAPED_COMPONENT_H

#include <SFML/Graphics.hpp>

class IShaped
{
public:
	virtual ~IShaped() { }

	virtual bool Contains(sf::Vector2f const& pos) = 0;
};

#endif