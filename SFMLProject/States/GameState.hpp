#pragma once

#include "../Input/PlayerInput.hpp"
#include "../World.hpp"
#include "State.hpp"


class GameState : public State
{
public:
			GameState(StateStack& stack, Context context);

	void	draw() override;
	bool	update(sf::Time dt) override;
	bool	handleEvent(const sf::Event& event) override;

private:
	World			m_world;
	PlayerInput&	m_player;
};
