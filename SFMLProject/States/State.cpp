#include "State.hpp"

#include "StateStack.hpp"


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, PlayerInput& player)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
{
}

State::State(StateStack& stack, Context context)
	: m_stack(&stack)
	, m_context(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID) const
{
	m_stack->pushState(stateID);
}

void State::requestStackPop() const
{
	m_stack->popState();
}

void State::requestStateClear() const
{
	m_stack->clearStates();
}

State::Context State::getContext() const
{
	return m_context;
}
