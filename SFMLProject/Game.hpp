#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Input/PlayerInput.hpp"
#include "States/StateStack.hpp"
#include "World.hpp"


class Game : private sf::NonCopyable
{
public:
			Game();
	void	run();

private:
	void	processInput();
	void	update(sf::Time deltaTime);
	void	render();

	void	updateStatistics(sf::Time elapsedTime);
	void	registerStates();

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		m_window;
	TextureHolder			m_textures;
	FontHolder				m_fonts;
	PlayerInput				m_player;

	StateStack				m_stateStack;

	sf::Text				m_statisticsText;
	sf::Time				m_statisticsUpdateTime;
	std::size_t				m_statisticsNumFrames;
};
