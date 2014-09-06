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

	inline sf::Text& Text() { return m_Text; }
	void Render(sf::RenderTarget& renderTarget) override;

	inline void SetAlignment(TextAlign align) { m_Align = align; }
	inline TextAlign GetAlignment() const { return m_Align; }

protected:
	sf::Vector2f GetScale(TransformComponent const* transform) const override;
	void ApplyAlignment();

private:
	sf::Text m_Text;
	TextAlign m_Align;
};

#endif