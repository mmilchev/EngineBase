#pragma once

#include "RendererComponent.h"
#include "IShaped.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class TransformComponent;

class SpriteRenderer
	: public RendererComponent, public IShaped
{
public:
	explicit SpriteRenderer(const std::string& textureName);

	void Awake() override;

	void Render(sf::RenderTarget& renderTarget) override;
	
	bool Contains(sf::Vector2f const& pos) override;

	void SetTextureByName(const std::string& texName);
	void SetSpriteSize(const sf::Vector2f& size);
	void SetDefaultOrigin(const sf::Vector2f& origin);
	void SetSpriteColor(const sf::Color& color);
	sf::Vector2f GetSpriteSize() const;
	bool ContainsPoint(float x, float y) const;
	bool Intersects(const SpriteRenderer& renderer) const;
	sf::Sprite& GetSprite();
	
	static sf::Vector2f GetTextureSize(const sf::Sprite& sp);
protected:
	sf::Vector2f GetScale(TransformComponent const* transform) const override;

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

