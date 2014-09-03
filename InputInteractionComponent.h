#ifndef INPUT_INTERACTION_COMPONENT_H
#define INPUT_INTERACTION_COMPONENT_H

#include "Component.h"
#include "IShaped.h"
#include <SFML/System/Vector2.hpp>

class SpriteRenderer;

class InputInteractionComponent
	: public Component
{
public:
	InputInteractionComponent();

	void Awake() override;
	void OnSignalingInitiazation() override;
	void OnDestruction() override;

	bool Contains(sf::Vector2i const& mousePos);
		
	inline bool GetHover() const { return m_Hover; }
	inline bool GetPressed() const { return m_Pressed; }
	inline void SetHover(bool hover) { m_Hover = hover; }
	inline void SetPressed(bool pressed) { m_Pressed = pressed; }
private:

	IShaped* m_ShapedComponent;

	bool m_Hover;
	bool m_Pressed;
	
};

#endif
