#include "InputInteractionComponent.h"
#include "GameObject.h"
#include "Application.h"
#include "CameraComponent.h"
#include "SpriteRenderer.h"
#include "Input.h"

InputInteractionComponent::InputInteractionComponent()
:m_Hover(false), m_Pressed(false), m_ShapedComponent(nullptr)
{
}

void InputInteractionComponent::Awake()
{
	m_ShapedComponent = m_GameObject->GetComponent<IShaped>();
}

void InputInteractionComponent::OnSignalingInitiazation()
{
	Input::RegisterInteractableObj(this);
}

void InputInteractionComponent::OnDestruction()
{
	Input::UnregisterInteractableObj(this);
}

bool InputInteractionComponent::Contains(sf::Vector2i const& mousePos)
{
	auto cameras = Application::GetGraphicsModule().GetCameras();
	for (auto const& camera : cameras)
	{
		if (camera->ShouldRenderLayer(m_GameObject->GetLayer())
			&& m_ShapedComponent->Contains(camera->ScreenToWorldSpace(mousePos)))
			return true;
	}
	return false;
}