#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"


class TitleState : public State
{
public:
			TitleState(StateStack& stack, Context context);

	void	draw() override;
	bool	update(sf::Time dt) override;
	bool	handleEvent(const sf::Event& event) override;

private:
	sf::Sprite			m_backgroundSprite;
	sf::Text			m_text;

	bool				m_showText;
	sf::Time			m_textEffectTime;
};
