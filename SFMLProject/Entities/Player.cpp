#include "Player.hpp"
#include "../Utilities/ResourceHolder.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


Textures::ID toTextureID(Player::Type type)
{
	switch (type)
	{
	case Player::Type::BibleThumpReverse:
		return Textures::ID::BibleThumpReverse;;
	}
	return Textures::ID::BibleThumpReverse;
}

Player::Player(Type type, const TextureHolder& textures)
	: m_type(type)
	, m_sprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
