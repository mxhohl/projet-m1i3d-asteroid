#include "Game.hpp"

#include "Settings.hpp"

#include <iostream>

Game::Game() : ok(true), quit(false), score(0) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " 
                  << SDL_GetError() 
                  << std::endl;
		ok = false;
        return;
	}

    Settings& settings = Settings::getInstance();

    window = SDL_CreateWindow(
        "Maxime Hohl's Asteroid Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        settings.getParameter<int>("window_width"),
        settings.getParameter<int>("window_height"),
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


    physicEngine = std::make_shared<PhysicEngine>();
    this->UpdateHandler::addObserver(physicEngine);

    player = std::make_shared<Player>(physicEngine);
    this->RenderingHandler::addObserver(player);
    this->KeyboardHandler::addObserver(player);
    this->UpdateHandler::addObserver(player);

    asteroids = std::make_shared<Asteroids>(10, physicEngine);
    this->UpdateHandler::addObserver(asteroids);
    this->RenderingHandler::addObserver(asteroids);
    asteroids->addObserver(std::shared_ptr<Game>(this));


    scoreText = std::make_shared<gui::Text>("Score: 00000");
    scoreText->setPosition({10, 10});
    scoreText->setScale(0.7);
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

        scoreText->render(renderer);

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
		        this->KeyboardHandler::notify(data);
		        break;
		}

	}

}

void Game::update(int& scoreDelta) {
    score += scoreDelta;
    scoreText->setText("Score: " + toStringPrefixed(score));
}
