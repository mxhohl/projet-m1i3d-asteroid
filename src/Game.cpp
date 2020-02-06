#include "Game.hpp"

#include <iostream>

Game::Game() : ok(true), quit(false) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " 
                  << SDL_GetError() 
                  << std::endl;
		ok = false;
        return;
	}

    window = SDL_CreateWindow(
        "Maxime Hohl's Asteroid Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        640, 480, 
        SDL_WINDOW_SHOWN
    );
    if (!window){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        ok = false;
        return;
    }

    renderer.create(window);

    if (!renderer.isOk()){
        SDL_DestroyWindow(window);
        std::cout << "Unable to create renderer" << std::endl;
        ok = false;
        return;
    }
}

Game::~Game() {
	SDL_Quit();
}

int Game::run() {
    if (!ok) {
        return 1;
    }

	while (!quit) {
		handleEvents();

        renderer.clear();
        this->Subject<Renderer>::notify(renderer);
        renderer.present();
	}

    return 0;
}

bool Game::isOk() const {
    return ok;
}

void Game::handleEvents() {
    SDL_Event event;

	while (!quit && SDL_PollEvent(&event)) {

		switch (event.type) {
            case SDL_QUIT:
			quit = true;
			break;
		}

	}

}
