#include "stdafx.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(const std::string& textureName)
{
	SetDefaultOrigin(sf::Vector2f(-1, -1));
	m_TextureName = textureName;
}

void SpriteRenderer::Awake()
{
	SetTextureByName(m_TextureName);
}

void SpriteRenderer::Render(sf::RenderTarget& renderTarget)
{
	ApplyTransformation(m_Sprite);
	renderTarget.draw(m_Sprite);
}

bool SpriteRenderer::Contains(sf::Vector2f const& pos)
{
	return m_Sprite.getGlobalBounds().contains(pos);
}

void SpriteRenderer::SetTextureByName(std::string const& texName)
{
	SetSpriteTexture(ResourceManager::GetTexture(texName));
	m_TextureName = texName;
}

void SpriteRenderer::SetSpriteTexture(const sf::Texture& tex )
{
	m_Sprite.setTexture(tex);
	auto bounds = m_Sprite.getLocalBounds();
	
	if(m_SpriteSize.x == 0 || m_SpriteSize.y == 0)
	{
		m_SpriteSize = GetTextureSize();
	}
	if(m_DefaultOrigin.x == -1 || m_DefaultOrigin.y == -1)
	{
		m_DefaultOrigin = sf::Vector2f(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
	}
	SetSpriteDefaultOrigin();
}

sf::Vector2f SpriteRenderer::GetTextureSize()
{
	return GetTextureSize(m_Sprite);
}

sf::Vector2f SpriteRenderer::GetTextureSize(const sf::Sprite& sp)
{
	auto size = sp.getTexture()->getSize();
	return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

sf::Vector2f SpriteRenderer::GetScale(TransformComponent const* transform) const
{
	auto textureSize = GetTextureSize(m_Sprite);
	auto scale = transform->Scale();
	float scaleFactorX = scale.x;
	float scaleFactorY = scale.y;
	if (!m_Sprite.getTexture()->isRepeated())
	{
		scaleFactorX *= (m_SpriteSize.x / textureSize.x);
		scaleFactorY *= (m_SpriteSize.y / textureSize.y);
	}

	return sf::Vector2f(scaleFactorX, scaleFactorY);
}

sf::Vector2f SpriteRenderer::GetSpriteSize() const
{
	return m_SpriteSize;
}

void SpriteRenderer::SetSpriteDefaultOrigin()
{
	SetSpriteOrigin(m_DefaultOrigin.x, m_DefaultOrigin.y);
}

void SpriteRenderer::SetSpriteOrigin( float x, float y )
{
	m_Sprite.setOrigin(x, y);
}

void SpriteRenderer::SetSpriteSize(const sf::Vector2f& size )
{
	m_SpriteSize = size;
}

void SpriteRenderer::SetDefaultOrigin(const sf::Vector2f& origin )
{
	m_DefaultOrigin = origin;
}

bool SpriteRenderer::ContainsPoint( float x, float y ) const
{
	return m_Sprite.getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool SpriteRenderer::Intersects(const SpriteRenderer& renderer ) const
{
	return renderer.m_Sprite.getGlobalBounds().intersects(m_Sprite.getGlobalBounds());
}

sf::Sprite& SpriteRenderer::GetSprite()
{
	return m_Sprite;
}

void SpriteRenderer::SetSpriteColor( const sf::Color& color )
{
	m_Sprite.setColor(color);
}
