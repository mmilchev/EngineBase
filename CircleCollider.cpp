#include "CircleCollider.h"
#include "Utils.h"

CircleCollider::CircleCollider(float radius)
:Collider()
{
	b2CircleShape* shape = new b2CircleShape();
	shape->m_radius = ToBox2DWorld(radius);
	SetShape(shape);
}