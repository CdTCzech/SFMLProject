#pragma once

#include "SceneNode.hpp"


class Entity : public SceneNode
{
public:
	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float x, float y);
	sf::Vector2f		getVelocity() const;

private:
	virtual void		updateCurrent(sf::Time dt) override;

private:
	sf::Vector2f		m_velocity;
};
