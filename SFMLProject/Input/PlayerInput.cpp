#include "PlayerInput.hpp"

#include <map>

#include "../Entities/PlayerEntity.hpp"
#include "Category.hpp"
#include "CommandQueue.hpp"


struct Mover
{
	Mover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (PlayerEntity& player, sf::Time) const
	{
		player.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

PlayerInput::PlayerInput()
{
	// Set initial key bindings
	m_keyBinding[sf::Keyboard::Up] = MoveUp;
	m_keyBinding[sf::Keyboard::Down] = MoveDown;
	m_keyBinding[sf::Keyboard::Left] = MoveLeft;
	m_keyBinding[sf::Keyboard::Right] = MoveRight;

	m_keyBinding[sf::Keyboard::W] = MoveUp;
	m_keyBinding[sf::Keyboard::S] = MoveDown;
	m_keyBinding[sf::Keyboard::A] = MoveLeft;
	m_keyBinding[sf::Keyboard::D] = MoveRight;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : m_actionBinding)
	{
		pair.second.category = Category::Player;
	}
}

void PlayerInput::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = m_keyBinding.find(event.key.code);
		if (found != m_keyBinding.end() && !isRealtimeAction(found->second))
		{
			commands.push(m_actionBinding[found->second]);
		}
	}
}

void PlayerInput::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : m_keyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(m_actionBinding[pair.second]);
		}
	}
}

void PlayerInput::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = m_keyBinding.begin(); itr != m_keyBinding.end(); )
	{
		if (itr->second == action)
		{
			m_keyBinding.erase(itr);
		}
		++itr;
	}

	// Insert new binding
	m_keyBinding[key] = action;
}

sf::Keyboard::Key PlayerInput::getAssignedKey(Action action) const
{
	for (auto pair : m_keyBinding)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Unknown;
}

void PlayerInput::initializeActions()
{
	const float playerSpeed = 200.f;

	m_actionBinding[MoveLeft].action = derivedAction<PlayerEntity>(Mover(-playerSpeed, 0.f));
	m_actionBinding[MoveRight].action = derivedAction<PlayerEntity>(Mover(+playerSpeed, 0.f));
	m_actionBinding[MoveUp].action = derivedAction<PlayerEntity>(Mover(0.f, -playerSpeed));
	m_actionBinding[MoveDown].action = derivedAction<PlayerEntity>(Mover(0.f, +playerSpeed));
}

bool PlayerInput::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}
