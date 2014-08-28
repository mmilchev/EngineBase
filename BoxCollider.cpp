#include "BoxCollider.h"
#include "Utils.h"

BoxCollider::BoxCollider(float width, float height)
{
	InitBoxShape(width, height, 0, 0);
}

BoxCollider::BoxCollider(float width, float height, float originX, float originY)
{
	InitBoxShape(width, height, originX, originY);
}

void BoxCollider::InitBoxShape(float width, float height, float originX, float originY)
{
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(ToBox2DWorld(width / 2), ToBox2DWorld(height / 2), ToBox2DWorld(b2Vec2(originX, originY)), 0);
	SetShape(shape);
}