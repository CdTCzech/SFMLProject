#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Game
{
public:
			Game();
	void	run();

private:
	void	processEvents();
	void	update();
	void	render();

private:
	sf::RenderWindow	mWindow;
	sf::CircleShape		mPlayer;
};
