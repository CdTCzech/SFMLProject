#include "TitleState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Utilities/ResourceHolder.hpp"
#include "../Utilities/Utility.hpp"


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, m_text()
	, m_showText(true)
	, m_textEffectTime(sf::Time::Zero)
{
	m_backgroundSprite.setTexture(context.textures->get(Textures::ID::TitleScreen));

	m_text.setFont(context.fonts->get(Fonts::ID::Main));
	m_text.setString("Press any key to start");
	centerOrigin(m_text);
	m_text.setPosition(context.window->getView().getSize() / 2.f);
	m_text.setColor(sf::Color::Red);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(m_backgroundSprite);

	if (m_showText)
	{
		window.draw(m_text);
	}
}

bool TitleState::update(sf::Time dt)
{
	m_textEffectTime += dt;

	if (m_textEffectTime >= sf::seconds(0.5f))
	{
		m_showText = !m_showText;
		m_textEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::ID::Menu);
	}

	return true;
}
