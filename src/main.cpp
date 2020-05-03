#include <iostream>

#include "Game.hpp"
#include "Logger.hpp"

void terminate() {
    std::cerr << "Terminating Asteroids..." << std::endl;
    abort();
}

int main(int, char**){
    std::set_terminate(terminate);

    try {
        Game& game = Game::getInstance();

        if (!game.isOk()) {
            FATAL("Unable to initialize game");
            return 1;
        }

        game.startGame();

        return game.run();
    } catch (std::exception& exception) {
        FATAL(sstr("Exception: ", exception.what()));
    } catch (...) {
        FATAL("Caught an unknown exception.");
	}

    return -1;
}
