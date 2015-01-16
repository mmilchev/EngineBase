#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <SFML/Window.hpp>
#include "QueuedVector.h"
#include "InputInteractionComponent.h"

class Input
{
public:
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);

	static bool GetButton(sf::Mouse::Button btn);
	static bool GetButtonDown(sf::Mouse::Button btn);
	static bool GetButtonUp(sf::Mouse::Button btn);

	static sf::Vector2i GetMousePos();

	static void ClearCurrentStates();
	static void Update();

	static void HandleEvent(const sf::Event& ev);

	static void RegisterInteractableObj(InputInteractionComponent* cmp);
	static void UnregisterInteractableObj(InputInteractionComponent* cmp);

private:

	static void MarkPressed(sf::Event const& ev);
	static void MarkClicked(sf::Event const& ev);
	static void MarkHover();

	struct MouseState
	{
		std::vector<sf::Mouse::Button> m_PressedButtons;
		std::vector<sf::Mouse::Button> m_ReleasedButtons;
		sf::Vector2i m_Position;
	};
	struct KeyboardState
	{
		std::vector<sf::Keyboard::Key> m_PressedKeys;
		std::vector<sf::Keyboard::Key> m_ReleasedKeys;
	};

	static MouseState sMouseState;
	static KeyboardState sKeyboardState;
	static QueuedVector<InputInteractionComponent*> sInteractableObjects;

	static bool sNeedsSorting;
};

#endif
