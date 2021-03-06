#pragma once

#include "SceneNode.hpp"


class Entity : public SceneNode
{
public:
	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float x, float y);
	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float x, float y);

	sf::Vector2f	getVelocity() const;

private:
	 void			updateCurrent(sf::Time deltaTime) override;

private:
	sf::Vector2f	m_velocity;
};
