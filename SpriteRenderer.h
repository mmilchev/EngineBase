#pragma once

#include "RendererComponent.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class TransformComponent;

class SpriteRenderer
	: public RendererComponent
{
public:
	explicit SpriteRenderer(const std::string& textureName);
	~SpriteRenderer();

	void Awake() override;

	void Render(sf::RenderTarget& renderTarget) override;
	
	void SetTextureByName(const std::string& texName);
	void SetSpriteSize(const sf::Vector2f& size);
	void SetDefaultOrigin(const sf::Vector2f& origin);
	void SetSpriteColor(const sf::Color& color);
	sf::Vector2f GetSpriteSize() const;
	bool ContainsPoint(float x, float y) const;
	bool Intersects(const SpriteRenderer& renderer) const;
	sf::Sprite& GetSprite();

	static void RenderSprite(sf::Sprite& sp, const sf::Vector2f& spriteSize, const TransformComponent& transform, sf::RenderTarget& target);
	static sf::Vector2f GetTextureSize(const sf::Sprite& sp);

private:
	sf::Sprite		m_Sprite;
	std::string		m_TextureName;
	sf::Vector2f	m_SpriteSize;
	sf::Vector2f	m_DefaultOrigin;

	void SetSpriteTexture(const sf::Texture& tex);
	sf::Vector2f GetTextureSize();

	virtual void SetSpriteDefaultOrigin();
	void SetSpriteOrigin(float x, float y);
};

