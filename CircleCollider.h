#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "Collider.h"

class CircleCollider
	:	public Collider
{
public:
	explicit CircleCollider(float radius);
};

#endif