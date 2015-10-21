#include "Game.h"

#include <SFML/Window/Event.hpp>


const float		Game::PlayerSpeed = 100.f;
const sf::Time	Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: m_window(sf::VideoMode(640, 480), "SFMLProject", sf::Style::Close)
	, m_player()
	, m_playerDown(false), m_playerLeft(false), m_playerRight(false), m_playerUp(false)
{
	m_player.setRadius(40.f);
	m_player.setPosition(100.f, 100.f);
	m_player.setFillColor(sf::Color::Green);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
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
	sf::Vector2f movement(0.f, 0.f);
	if (m_playerDown)
	{
		movement.y += PlayerSpeed;
	}
	if (m_playerLeft)
	{
		movement.x -= PlayerSpeed;
	}
	if (m_playerRight)
	{
		movement.x += PlayerSpeed;
	}
	if (m_playerUp)
	{
		movement.y -= PlayerSpeed;
	}

	m_player.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_player);
	m_window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::A:
		m_playerLeft = isPressed;
		break;
	case sf::Keyboard::D:
		m_playerRight = isPressed;
		break;
	case sf::Keyboard::S:
		m_playerDown = isPressed;
		break;
	case sf::Keyboard::W:
		m_playerUp = isPressed;
		break;
	default:
		break;
	}
}
