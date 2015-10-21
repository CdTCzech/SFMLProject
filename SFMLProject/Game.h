#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>


class Game
{
public:
			Game();
	void	run();

private:
	void	processEvents();
	void	update();
	void	render();

	void	handlePlayerInput(sf::Keyboard::Key key, bool b);

private:
	sf::RenderWindow	m_window;
	sf::CircleShape		m_player;

	bool m_playerDown, m_playerLeft, m_playerRight, m_playerUp;
};
