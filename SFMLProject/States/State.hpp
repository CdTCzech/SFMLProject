#pragma once

#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utilities/ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"


namespace sf
{
	class RenderWindow;
}

class StateStack;
class PlayerInput;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, PlayerInput& player);

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		PlayerInput*		player;
	};

public:
					State(StateStack& stack, Context context);
	virtual			~State();

	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handleEvent(const sf::Event& event) = 0;

protected:
	void			requestStackPush(States::ID stateID) const;
	void			requestStackPop() const;
	void			requestStateClear() const;

	Context			getContext() const;

private:
	StateStack*		m_stack;
	Context			m_context;
};
