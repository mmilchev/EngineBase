#include "Collider.h"


Collider::Collider()
:m_Shape(nullptr), m_Fixture(nullptr)
{
	m_FixtureDef.density = 1;
}

void Collider::SetDefIsSensor(bool isSensor)
{
	m_FixtureDef.isSensor = isSensor;
}

void Collider::SetDefFriction(float friction)
{
	m_FixtureDef.friction = friction;
}

void Collider::SetDefRestitution(float restitution)
{
	m_FixtureDef.restitution = restitution;
}

void Collider::SetDefCategoryBits(uint16 bits)
{
	m_FixtureDef.filter.categoryBits = bits;
}

void Collider::SetDefCollisionMask(uint16 mask)
{
	m_FixtureDef.filter.maskBits = mask;
}

b2FixtureDef const& Collider::GetFixtureDef() const
{
	return m_FixtureDef;
}

void Collider::SetFixture(b2Fixture* fixture)
{
	m_Fixture = fixture;
	m_Fixture->SetUserData(m_GameObject);
}

void Collider::SetShape(b2Shape* shape)
{
	m_Shape = shape;
	m_FixtureDef.shape = m_Shape;
}