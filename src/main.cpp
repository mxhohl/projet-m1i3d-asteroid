#include <iostream>

#include "Game.hpp"
#include "Logger.hpp"

void terminate() {
    std::cerr << "Terminating Asteroids..." << std::endl;
    abort();
}

int main(int, char**){
    std::set_terminate(terminate);

    DEBUG("test debug");
    INFO("test info");
    WARN("test warning");
    ERROR("test error");
    FATAL("test fatal");

    try {
        Game& game = Game::getInstance();

        if (!game.isOk()) {
            std::cerr << "Unable to initialize game" << std::endl;
            SDL_ShowSimpleMessageBox(
                    SDL_MESSAGEBOX_ERROR,
                    "Error",
                    "Unable to initialize game.",
                    nullptr
            );
            return 1;
        }

        game.startGame();

        return game.run();
    } catch (std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
        terminate();
    } catch (...) {
	    std::cerr << "Caught an unknown exception." << std::endl;
	    terminate();
	}

    return -1;
}
