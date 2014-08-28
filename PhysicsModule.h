#ifndef PHYSICS_MODULE_H
#define PHYSICS_MODULE_H

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <queue>

class RigidBody;

class PhysicsModule
{
public:
	PhysicsModule();

	void QueueRigidBodyForInitialization(RigidBody* body);

	void InitQueuedBodies();
	void StepWorld();

	void SetTimeStep(float timeStep);
	void SetVelocityItterations(int itterations);
	void SetPositionItterations(int itterations);

	static const b2World* GetWorld();
	static void RayCast(b2RayCastCallback* callback, sf::Vector2f const& origin, sf::Vector2f const& destination);
private:
	std::unique_ptr<b2World> m_World;
	std::queue<RigidBody*> m_InstQueue;

	float m_TimeStep;
	int	m_VelocityItterations;
	int	m_PositionItterations;
};
#endif
