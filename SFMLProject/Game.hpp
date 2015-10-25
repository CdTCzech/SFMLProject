#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "World.hpp"


class Game : private sf::NonCopyable
{
public:
			Game();
	void	run();

private:
	void	processEvents();
	void	update(sf::Time deltaTime);
	void	render();

	void	handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void	updateStatistics(sf::Time elapsedTime);

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		m_window;
	World					m_world;

	sf::Font				m_font;
	sf::Text				m_statisticsText;
	sf::Time				m_statisticsUpdateTime;
	std::size_t				m_statisticsNumFrames;
};
