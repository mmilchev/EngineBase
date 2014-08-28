#ifndef COLLISION_CALLBACK_H
#define COLLISION_CALLBACK_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

struct CollisionData;

class CollisionCallback
	: public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};
#endif