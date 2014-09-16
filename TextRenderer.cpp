#include "TextRenderer.h"
#include "TransformComponent.h"
#include "GameObject.h"

TextRenderer::TextRenderer()
	: m_ShadowSize(0), m_ShadowColor(0, 0, 0, 255)
{
}

void TextRenderer::Render(sf::RenderTarget& renderTarget)
{
	if (m_ShadowSize > 0.1)
	{
		auto oldPos = m_GameObject->Transform()->Position();
		auto oldColor = m_Text.getColor();

		m_Text.setColor(m_ShadowColor); 
		m_GameObject->Transform()->Translate(sf::Vector2f(m_ShadowSize, m_ShadowSize));

		ApplyAlignment();
		ApplyTransformation(m_Text);
		renderTarget.draw(m_Text);

		m_Text.setColor(oldColor);
		m_GameObject->Transform()->SetPosition(oldPos);
	}

	ApplyAlignment();
	ApplyTransformation(m_Text);
	renderTarget.draw(m_Text);
}

sf::Vector2f TextRenderer::GetScale(TransformComponent const* transform) const
{
	return transform->Scale();
}

void TextRenderer::ApplyAlignment()
{
	auto textRect = m_Text.getLocalBounds();
	switch (m_Align)
	{
	case TopLeft:
		m_Text.setOrigin(textRect.left, textRect.top);

		break;
	case Center:
		m_Text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		break;
	default: break;
	}
}
