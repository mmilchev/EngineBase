#include "DynamicBehaviour.h"
#include "GameObject.h"
#include "CollisionData.h"

DynamicBehaviour::DynamicBehaviour()
{
}

void DynamicBehaviour::Update()
{
}

void DynamicBehaviour::LateUpdate()
{
}

void DynamicBehaviour::OnCollisionEnter(CollisionData& collision)
{
}

void DynamicBehaviour::OnCollisionExit(CollisionData& collision)
{
}

void DynamicBehaviour::OnClicked()
{
}

void DynamicBehaviour::OnMouseEnter()
{
}

void DynamicBehaviour::OnMouseLeave()
{
}

void DynamicBehaviour::SetOwner(GameObject* obj)
{
	Component::SetOwner(obj);
	obj->PushDynamicBehaviour(this);
}