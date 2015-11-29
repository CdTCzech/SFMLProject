#include "GameState.hpp"


#include <SFML/Graphics/Texture.hpp> // Needed because of forward declaration in ResourceIdentifiers


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, m_world(*context.window)
	, m_player(*context.player)
{
}

void GameState::draw()
{
	m_world.draw();
}

bool GameState::update(sf::Time dt)
{
	m_world.update(dt);

	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(States::ID::Pause);
	}

	return true;
}
