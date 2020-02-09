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
        1280, 720,
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

    player = std::make_shared<Player>();
    this->Subject<Renderer>::addObserver(player);
    this->Subject<KeyboardEventData>::addObserver(player);
    this->Subject<double>::addObserver(player);
}

Game::~Game() {
	SDL_Quit();
}

int Game::run() {
    if (!ok) {
        return 1;
    }

    Uint32 lastUpdate = SDL_GetTicks();

	while (!quit) {
		handleEvents();

        renderer.clear();
        this->Subject<Renderer>::notify(renderer);
        renderer.present();

        Uint32 currentTime = SDL_GetTicks();
        double dt = (currentTime - lastUpdate) / 1000.;
        this->Subject<double>::notify(dt);
        lastUpdate = currentTime;
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
		    case SDL_KEYDOWN:
		    case SDL_KEYUP:
		        KeyboardEventData data(
		                event.key.type == SDL_KEYUP
		                    ? KeyboardEventData::Release
		                    : KeyboardEventData::Press,
		                event.key.keysym.scancode,
		                event.key.keysym.sym
                );
		        this->Subject<KeyboardEventData>::notify(data);
		        break;
		}

	}

}
