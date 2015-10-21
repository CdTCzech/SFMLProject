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
	void	update(sf::Time deltaTime);
	void	render();

	void	handlePlayerInput(sf::Keyboard::Key key, bool b);

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow	m_window;
	sf::CircleShape		m_player;

	bool	m_playerDown, m_playerLeft, m_playerRight, m_playerUp;
};
