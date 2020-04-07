#include <iostream>

#include "Game.hpp"

int main(int, char**){
	Game& game = Game::getInstance();

	if (!game.init()) {
	    std::cerr << "Unable to initialize game" << std::endl;
	    SDL_ShowSimpleMessageBox(
	            SDL_MESSAGEBOX_ERROR,
	            "Error",
	            "Unable to initialize game.",
	            nullptr
        );
	    return 1;
	}

	return game.run();
}
