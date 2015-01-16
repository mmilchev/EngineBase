#include "Input.h"
#include <SFML/Window/Event.hpp>
#include "Application.h"

Input::MouseState		Input::sMouseState;
Input::KeyboardState	Input::sKeyboardState;
QueuedVector<InputInteractionComponent*> Input::sInteractableObjects;
bool Input::sNeedsSorting;

bool Input::GetKey(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool Input::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(sKeyboardState.m_PressedKeys.begin(), sKeyboardState.m_PressedKeys.end(), key) != sKeyboardState.m_PressedKeys.end();
}

bool Input::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(sKeyboardState.m_ReleasedKeys.begin(), sKeyboardState.m_ReleasedKeys.end(), key) != sKeyboardState.m_ReleasedKeys.end();
}

bool Input::GetButton(sf::Mouse::Button btn)
{
	return sf::Mouse::isButtonPressed(btn);
}

bool Input::GetButtonDown(sf::Mouse::Button btn)
{
	return std::find(sMouseState.m_PressedButtons.begin(), sMouseState.m_PressedButtons.end(), btn) != sMouseState.m_PressedButtons.end();
}

bool Input::GetButtonUp(sf::Mouse::Button btn)
{
	return std::find(sMouseState.m_ReleasedButtons.begin(), sMouseState.m_ReleasedButtons.end(), btn) != sMouseState.m_ReleasedButtons.end();
}

sf::Vector2i Input::GetMousePos()
{
	return sMouseState.m_Position;
}

void Input::ClearCurrentStates()
{
	sMouseState = MouseState();
	sKeyboardState = KeyboardState();
	sInteractableObjects.ProcessQueued();

	if (sNeedsSorting)
	{
		sInteractableObjects.Sort(
			[](InputInteractionComponent const* lhs, InputInteractionComponent const* rhs) { return lhs->GetOrder() > rhs->GetOrder(); });
		sNeedsSorting = false;
	}

	sMouseState.m_Position = sf::Mouse::getPosition(Application::GetWindow());
}

void Input::Update()
{
	MarkHover();
}

void Input::HandleEvent(sf::Event const& ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseButtonPressed:
		sMouseState.m_PressedButtons.push_back(ev.mouseButton.button);
		MarkPressed(ev);
		break;
	case sf::Event::MouseButtonReleased:
		sMouseState.m_ReleasedButtons.push_back(ev.mouseButton.button);
		MarkClicked(ev);
		break;
	case sf::Event::KeyPressed:
		sKeyboardState.m_PressedKeys.push_back(ev.key.code);
		break;
	case sf::Event::KeyReleased:
		sKeyboardState.m_ReleasedKeys.push_back(ev.key.code);
		break;
	default:
		break;
	}
}

void Input::RegisterInteractableObj(InputInteractionComponent* cmp)
{
	sInteractableObjects.Add(cmp);
	sNeedsSorting = true;
}

void Input::UnregisterInteractableObj(InputInteractionComponent* cmp)
{
	sInteractableObjects.Remove(cmp);
}

void Input::MarkPressed(sf::Event const& ev)
{
	auto& raw = sInteractableObjects.GetRawData();
	for (auto const obj : raw)
	{
		if (obj->Contains(sMouseState.m_Position))
		{
			obj->SetPressed(true);
			break;
		}
	}
}

void Input::MarkClicked(sf::Event const& ev)
{
	auto& raw = sInteractableObjects.GetRawData();
	for (auto const obj : raw)
	{
		if (obj->Contains(sMouseState.m_Position)
			&& obj->GetPressed())
		{
			obj->GetGameObject()->OnClicked();
			break;
		}
	}

	for (auto const obj : raw)
	{
		//Pressed should be false at the end no matter what
		obj->SetPressed(false);
	}
}

void Input::MarkHover()
{
	auto& raw = sInteractableObjects.GetRawData();
	auto size = Application::GetWindow().getSize();
	auto windowRect = sf::IntRect(0, 0, size.x, size.y);
	for (auto const obj : raw)
	{
		bool contains = windowRect.contains(sMouseState.m_Position) &&
			obj->Contains(sMouseState.m_Position);
		if (contains && !obj->GetHover())
		{
			obj->GetGameObject()->OnMouseEnter();
			obj->SetHover(contains);
			break;
		}
		else if (!contains && obj->GetHover())
		{
			obj->GetGameObject()->OnMouseLeave();
			obj->SetHover(contains);
			break;
		}
	}
}