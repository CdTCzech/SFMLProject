#include "Game.hpp"

#include <SFML/Window/Event.hpp>

#include "States/GameState.hpp"
#include "States/MenuState.hpp"
#include "States/PauseState.hpp"
#include "States/TitleState.hpp"


const sf::Time	Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: m_window(sf::VideoMode(640, 480), "SFMLProject", sf::Style::Close)
	, m_textures()
	, m_fonts()
	, m_player()
	, m_stateStack(State::Context(m_window, m_textures, m_fonts, m_player))
	, m_statisticsText()
	, m_statisticsUpdateTime()
	, m_statisticsNumFrames(0)
{
	m_window.setKeyRepeatEnabled(false);

	m_fonts.load(Fonts::ID::Main, "Resources/Fonts/Sansation.ttf");
	m_textures.load(Textures::ID::TitleScreen, "Resources/Textures/TitleScreen.png");

	m_statisticsText.setFont(m_fonts.get(Fonts::ID::Main));
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(12);

	registerStates();
	m_stateStack.pushState(States::ID::Title);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);

			if (m_stateStack.isEmpty())
			{
				m_window.close();
			}
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	m_stateStack.update(deltaTime);
}

void Game::render()
{
	m_window.clear();

	m_stateStack.draw();

	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_statisticsText);
	m_window.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	m_statisticsUpdateTime += elapsedTime;
	m_statisticsNumFrames += 1;

	if (m_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		m_statisticsText.setString(
			"Frames / Second: " + std::to_string(m_statisticsNumFrames) + "\n" +
			"Time / Update: " + std::to_string(m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames) + "us"
		);

		m_statisticsUpdateTime -= sf::seconds(1.0f);
		m_statisticsNumFrames = 0;
	}
}

void Game::registerStates()
{
	m_stateStack.registerState<TitleState>(States::ID::Title);
	m_stateStack.registerState<MenuState>(States::ID::Menu);
	m_stateStack.registerState<GameState>(States::ID::Game);
	m_stateStack.registerState<PauseState>(States::ID::Pause);
}
