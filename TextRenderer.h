#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "RendererComponent.h"

class TextRenderer
	: public RendererComponent
{
public:
	enum TextAlign
	{
		TopLeft,
		Center,
		Custom
	};

	TextRenderer();

	inline sf::Text& Text() { return m_Text; }
	void Render(sf::RenderTarget& renderTarget) override;

	inline void SetAlignment(TextAlign align) { m_Align = align; }
	inline TextAlign GetAlignment() const { return m_Align; }
	inline void SetShadowSize(float size) { m_ShadowSize = size; }
	inline void SetShadowColor(sf::Color const& color) { m_ShadowColor = color; }

protected:
	sf::Vector2f GetScale(TransformComponent const* transform) const override;
	void ApplyAlignment();

private:
	float m_ShadowSize;
	sf::Color m_ShadowColor;

	sf::Text m_Text;
	TextAlign m_Align;
};

#endif