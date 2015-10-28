#pragma once

#include <map>

#include <SFML/Window/Event.hpp>

#include "Command.hpp"


class CommandQueue;

class PlayerInput
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

public:
						PlayerInput();

	void				handleEvent(const sf::Event& event, CommandQueue& commands);
	void				handleRealtimeInput(CommandQueue& commands);

	void				assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key	getAssignedKey(Action action) const;

private:
	void				initializeActions();
	static bool			isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action>	m_keyBinding;
	std::map<Action, Command>			m_actionBinding;
};
