#include "PhysicsModule.h"
#include "RigidBody.h"
#include "GameTime.h"
#include "CollisionCallback.h"
#include "Application.h"
#include "Utils.h"

PhysicsModule::PhysicsModule()
:m_TimeStep(1 / 240.f), m_VelocityItterations(8), m_PositionItterations(3)
{
	m_World = std::unique_ptr<b2World>(new b2World(b2Vec2(0, 0)));
	m_World->SetContactListener(new CollisionCallback());
}

void PhysicsModule::QueueRigidBodyForInitialization(RigidBody* body)
{
	m_InstQueue.push(body);
}

void PhysicsModule::InitQueuedBodies()
{
	while (!m_InstQueue.empty())
	{
		auto body = m_InstQueue.front();
		body->InitBody(m_World.get());
		m_InstQueue.pop();
	}
}

void PhysicsModule::StepWorld()
{
	//Variable timestep for now
	m_World->Step(GameTime::DeltaTime(), m_VelocityItterations, m_PositionItterations);
}

void PhysicsModule::SetTimeStep(float timeStep)
{
	m_TimeStep = timeStep;
}

void PhysicsModule::SetVelocityItterations(int itterations)
{
	m_VelocityItterations = itterations;
}

void PhysicsModule::SetPositionItterations(int itterations)
{
	m_PositionItterations = itterations;
}

const b2World* PhysicsModule::GetWorld()
{
	return Application::GetPhysicsModule().m_World.get();
}

void PhysicsModule::RayCast(b2RayCastCallback* callback, sf::Vector2f const& origin, sf::Vector2f const& destination)
{
	GetWorld()->RayCast(callback, ToBox2DWorld(SfToBox(origin)), ToBox2DWorld(SfToBox(destination)));
}