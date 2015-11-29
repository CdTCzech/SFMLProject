#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"


class MenuState : public State
{
public:
			MenuState(StateStack& stack, Context context);

	void	draw() override;
	bool	update(sf::Time dt) override;
	bool	handleEvent(const sf::Event& event) override;

	void	updateOptionText();


private:
	enum OptionNames
	{
		Play,
		Exit,
	};

private:
	sf::Sprite				m_backgroundSprite;

	std::vector<sf::Text>	m_options;
	std::size_t				m_optionIndex;
};
