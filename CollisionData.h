#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "Collider.h"

struct CollisionData
{
	inline b2Body*	GetBody()	{ return m_Fixture->GetBody(); }
	GameObject*	m_GameObject;
	b2Fixture*	m_Fixture;
	b2Contact*	m_Contact;
};

#endif