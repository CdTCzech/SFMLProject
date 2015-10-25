#include "Game.hpp"

#include <iostream>


int main(int /*argc*/, char** /*argv*/)
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}
