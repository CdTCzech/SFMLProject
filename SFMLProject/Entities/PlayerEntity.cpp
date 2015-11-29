#include "PlayerEntity.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Input/Category.hpp"
#include "../Utilities/ResourceHolder.hpp"
#include "../Utilities/Utility.hpp"


Textures::ID toTextureID(PlayerEntity::Type type)
{
	switch (type)
	{
	case PlayerEntity::Type::BibleThumpReverse:
		return Textures::ID::BibleThumpReverse;
	}
	return Textures::ID::BibleThumpReverse;
}

PlayerEntity::PlayerEntity(Type type, const TextureHolder& textures)
	: m_type(type)
	, m_sprite(textures.get(toTextureID(type)))
{
	centerOrigin(m_sprite);
}

unsigned int PlayerEntity::getCategory() const
{
	switch (m_type)
	{
	case Type::BibleThumpReverse:
		return Category::Player;
	default:
		return Category::Player;
	}
}

void PlayerEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
