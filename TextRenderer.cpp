#include "TextRenderer.h"
#include "TransformComponent.h"

void TextRenderer::Render(sf::RenderTarget& renderTarget)
{
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
		m_Text.setOrigin(textRect.left,	textRect.top);

		break;
	case Center:
		m_Text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		break;
	default: break;
	}
}