#pragma once

#include "Entity.hpp"
#include "../Utilities/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Player : public Entity
{
public:
	enum class Type
	{
		BibleThumpReverse,
	};

public:
					Player(Type type, const TextureHolder& textures);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Type			m_type;
	sf::Sprite		m_sprite;
};
