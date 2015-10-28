#include "Entity.hpp"


void Entity::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::setVelocity(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

sf::Vector2f Entity::getVelocity() const
{
	return m_velocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	m_velocity += velocity;
}

void Entity::accelerate(float x, float y)
{
	m_velocity.x += x;
	m_velocity.y += y;
}

void Entity::updateCurrent(sf::Time deltaTime)
{
	move(m_velocity * deltaTime.asSeconds());
}
