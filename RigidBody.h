#pragma once

#include "DynamicBehaviour.h"
#include "Transform2D.h"
#include <Box2D/Box2D.h>
#include <vector>

class RigidBody
	: public DynamicBehaviour
{
public:
	RigidBody();
	~RigidBody();
	
	void InitBody(b2World* world);

	void SetBodyDef(const b2BodyDef& def);

	void SetDefPosition(float x, float y);
	void SetDefBodyType(b2BodyType type);
	void SetDefAngularVelocity(float vel);
	void SetDefLinearVelocity(const b2Vec2& vel);

	void SetBodyRotation(float angle);
	float GetBodyRotation() const;
	b2Vec2 GetBodyPosition() const;

	b2Body* GetBody();

	void Awake() override;
	void LateUpdate() override;
	void OnSignalingInitiazation() override;
	void OnDestruction() override;
private:

	b2Body*		m_Body;	
	b2BodyDef	m_BodyDef;
	Transform2D m_Transform;
};

