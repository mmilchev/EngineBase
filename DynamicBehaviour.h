#ifndef DYNAMIC_BEHAVIOUR_H
#define DYNAMIC_BEHAVIOUR_H

#include "Component.h"

struct CollisionData;

class DynamicBehaviour
	: public Component
{
protected:
	DynamicBehaviour();

public:
	virtual void Update();
	virtual void LateUpdate();

	//Collision callbacks
	virtual void OnCollisionEnter(CollisionData& collision);
	virtual void OnCollisionExit(CollisionData& collision);

	//Input interaction
	virtual void OnClicked();
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();

	void SetOwner(GameObject* obj) override;
	//Add OnCollision events
};

#endif