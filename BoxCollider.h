#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"

class BoxCollider
	: public Collider
{
public:
	BoxCollider(float width, float height);
	BoxCollider(float width, float height, float originX, float originY);
private:
	void InitBoxShape(float width, float height, float originX, float originY);
};

#endif