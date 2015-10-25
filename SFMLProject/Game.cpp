#include "Game.hpp"

#include <SFML/Window/Event.hpp>


const sf::Time	Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: m_window(sf::VideoMode(640, 480), "SFMLProject", sf::Style::Close)
	, m_world(m_window)
	, m_font()
	, m_statisticsText()
	, m_statisticsUpdateTime()
	, m_statisticsNumFrames(0)
{
	m_font.loadFromFile("Resources/Fonts/Sansation.ttf");
	m_statisticsText.setFont(m_font);
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(12);
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
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	m_world.update(deltaTime);
}

void Game::render()
{
	m_window.clear();

	m_world.draw();

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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}
