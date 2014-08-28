#include "stdafx.h"
#include "RigidBody.h"
#include "TransformComponent.h"
#include "Utils.h"
#include "Collider.h"
#include "GameObject.h"
#include "Application.h"

RigidBody::RigidBody()
:m_Body(nullptr)
{
	m_BodyDef.type = b2BodyType::b2_dynamicBody;
}


RigidBody::~RigidBody()
{
}

void RigidBody::InitBody(b2World* world)
{
	assert(m_Body == nullptr);

	auto transform = m_GameObject->Transform();
	m_BodyDef.position = ToBox2DWorld(SfToBox(transform->Position()));
	m_Body = world->CreateBody(&m_BodyDef);
		
	auto colliders = m_GameObject->GetComponents<Collider>();
	for (auto collider: colliders)
	{
		auto fixtureDef = collider->GetFixtureDef();
		auto fixture = m_Body->CreateFixture(&fixtureDef);
		collider->SetFixture(fixture);
	}

	m_Body->SetUserData(m_GameObject);

	SetBodyRotation(transform->Rotation());
}

void RigidBody::Awake()
{
}

void RigidBody::LateUpdate()
{
	TransformComponent* transComp = m_GameObject->Transform();
	
	//Check if transform has changed
	auto& trans = transComp->GetLocalTransform();
	if (trans != m_Transform)
		m_Body->SetTransform(SfToBox(ToBox2DWorld(trans.m_Position)), DegToRad(trans.m_Rotation));

	transComp->SetPosition(BoxToSf(GetBodyPosition()));
	transComp->SetRotation(GetBodyRotation());
	
	m_Transform = trans;
}

void RigidBody::OnSignalingInitiazation()
{
	Application::GetPhysicsModule().QueueRigidBodyForInitialization(this);
}

void RigidBody::OnDestruction()
{
	if (m_Body != nullptr)
	{
		//Fixtures are destroyed automatically

		auto world = m_Body->GetWorld();
		m_Body->SetUserData(nullptr);
		world->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}

void RigidBody::SetBodyDef(const b2BodyDef& def )
{
	m_BodyDef = def;
}

void RigidBody::SetBodyRotation( float angle )
{
	m_Body->SetTransform(m_Body->GetTransform().p, DegToRad(angle));
}

float RigidBody::GetBodyRotation() const
{
	return RadToDeg(m_Body->GetTransform().q.GetAngle());
}

b2Vec2 RigidBody::GetBodyPosition() const
{
	b2Vec2 pos = m_Body->GetTransform().p;
	return FromBox2DWorld(pos);
}

void RigidBody::SetDefPosition( float x, float y )
{
	m_BodyDef.position = b2Vec2(x, y);
}

void RigidBody::SetDefAngularVelocity( float vel )
{
	m_BodyDef.angularVelocity = vel;
}

void RigidBody::SetDefLinearVelocity(b2Vec2 const& vel)
{
	m_BodyDef.linearVelocity = vel;
}

void RigidBody::SetDefBodyType(b2BodyType type)
{
	m_BodyDef.type = type;
}

b2Body* RigidBody::GetBody()
{
	return this->m_Body;
}
