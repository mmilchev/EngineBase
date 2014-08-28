#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include <Box2D/Box2D.h>

class Collider
	: public Component
{
public:
	void SetDefIsSensor(bool isSensor);
	void SetDefFriction(float friction);
	void SetDefRestitution(float restitution);

	void SetDefCategoryBits(uint16 bits);
	void SetDefCollisionMask(uint16 mask);

	const b2FixtureDef& GetFixtureDef() const;
	void SetFixture(b2Fixture* fixture);
protected:
	Collider();
	void SetShape(b2Shape* shape);

private:
	b2Shape*		m_Shape;
	b2Fixture*		m_Fixture;
	b2FixtureDef	m_FixtureDef;
};

#endif