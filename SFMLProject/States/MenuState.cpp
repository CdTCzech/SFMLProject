#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Utilities/ResourceHolder.hpp"
#include "../Utilities/Utility.hpp"


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, m_options()
	, m_optionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::ID::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	m_backgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	m_options.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	m_options.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(m_backgroundSprite);

	for (const sf::Text& text : m_options)
	{
		window.draw(text);
	}
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_optionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::ID::Game);
		}
		else if (m_optionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (m_optionIndex > 0)
		{
			--m_optionIndex;
		}
		else
		{
			m_optionIndex = m_options.size() - 1;
		}

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (m_optionIndex < m_options.size() - 1)
		{
			++m_optionIndex;
		}
		else
		{
			m_optionIndex = 0;
		}

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (m_options.empty())
		return;

	// White all texts
	for (sf::Text& text : m_options)
	{
		text.setColor(sf::Color::White);
	}

	// Red the selected text
	m_options[m_optionIndex].setColor(sf::Color::Red);
}
