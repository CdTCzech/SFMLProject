#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>


class Game : private sf::NonCopyable
{
public:
			Game();
	void	run();

private:
	void	processEvents();
	void	update(sf::Time deltaTime);
	void	render();

	void	handlePlayerInput(sf::Keyboard::Key key, bool b);
	void	updateStatistics(sf::Time elapsedTime);

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow	m_window;
	sf::Texture			m_texture;
	sf::Sprite			m_player;
	sf::Font			m_font;
	sf::Text			m_statisticsText;
	sf::Time			m_statisticsUpdateTime;

	std::size_t	m_statisticsNumFrames;
	bool		m_playerDown, m_playerLeft, m_playerRight, m_playerUp;
};