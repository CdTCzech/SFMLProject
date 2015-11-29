#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"


class PauseState : public State
{
public:
			PauseState(StateStack& stack, Context context);

	void	draw() override;
	bool	update(sf::Time dt) override;
	bool	handleEvent(const sf::Event& event) override;

private:
	sf::Sprite	m_backgroundSprite;
	sf::Text	m_pausedText;
	sf::Text	m_instructionText;
};
