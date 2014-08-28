#include "CollisionCallback.h"
#include "CollisionData.h"

#include "GameObject.h"

//Code repetition in Begin and Exit, sacrificing maintainability for speed and readability 
void CollisionCallback::BeginContact(b2Contact* contact)
{
	CollisionData dataA, dataB;
	GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());
	
	if (!(gameObjectA->IsDynamic() || gameObjectB->IsDynamic()))
		return;
	
	dataA.m_GameObject = gameObjectA;
	dataB.m_GameObject = gameObjectB;
	dataA.m_Fixture = contact->GetFixtureA();
	dataB.m_Fixture = contact->GetFixtureB();
	dataA.m_Contact = contact;
	dataB.m_Contact = contact;

	if (gameObjectA->IsDynamic())
		gameObjectA->OnCollisionEnter(dataB);
	if(gameObjectB->IsDynamic())
		gameObjectB->OnCollisionEnter(dataA);
}

void CollisionCallback::EndContact(b2Contact* contact)
{
	CollisionData dataA, dataB;
	GameObject* gameObjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* gameObjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

	if (!(gameObjectA->IsDynamic() || gameObjectB->IsDynamic()))
		return;

	dataA.m_GameObject = gameObjectA;
	dataB.m_GameObject = gameObjectB;
	dataA.m_Fixture = contact->GetFixtureA();
	dataB.m_Fixture = contact->GetFixtureB();
	dataA.m_Contact = contact;
	dataB.m_Contact = contact;

	if (gameObjectA->IsDynamic())
		gameObjectA->OnCollisionExit(dataB);
	if (gameObjectB->IsDynamic())
		gameObjectB->OnCollisionExit(dataA);
}