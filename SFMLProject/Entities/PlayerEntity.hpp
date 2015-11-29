#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "../Utilities/ResourceIdentifiers.hpp"
#include "Entity.hpp"


class PlayerEntity : public Entity
{
public:
	enum class Type
	{
		BibleThumpReverse,
	};

public:
					PlayerEntity(Type type, const TextureHolder& textures);

	unsigned int	getCategory() const override;

private:
	void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Type			m_type;
	sf::Sprite		m_sprite;
};
