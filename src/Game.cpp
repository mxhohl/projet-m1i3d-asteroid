#include "Game.hpp"

#include "Settings.hpp"

#include <iostream>

Game::Game() : ok(false), quit(false), paused(false), score(0),
               window(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: "
                  << SDL_GetError()
                  << std::endl;
        ok = false;
    }
}

Game::~Game() {
	SDL_Quit();
}

bool Game::init() {
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
        return false;
    }

    renderer.create(window);

    if (!renderer.isOk()){
        SDL_DestroyWindow(window);
        std::cout << "Unable to create renderer" << std::endl;
        ok = false;
        return false;
    }


    physicEngine = std::make_shared<PhysicEngine>();
    this->UpdateHandler::addObserver(physicEngine);

    player = std::make_shared<Player>(physicEngine);
    this->RenderingHandler::addObserver(player);
    this->KeyboardHandler::addObserver(player);
    this->UpdateHandler::addObserver(player);
    player->setScale(5);
    player->setPosition({
        settings.getParameter<int>("window_width") / 2.f,
        settings.getParameter<int>("window_height") / 2.f
    });

    asteroids = std::make_shared<Asteroids>(10, physicEngine);
    this->UpdateHandler::addObserver(asteroids);
    this->RenderingHandler::addObserver(asteroids);


    gui = std::make_shared<gui::Gui>();
    this->RenderingHandler::addObserver(gui);

    scoreText = gui->create<gui::Text>();
    scoreText->setText("Score: 00000");
    scoreText->setPosition({10, 10});
    scoreText->setCharacterSize(20);
    scoreText->setColor(Color::White());

    middleScreenPanel = gui->create<gui::Panel>();
    middleScreenPanel->setColor({200, 200, 200, 70});
    middleScreenPanel->setWidth(300);
    middleScreenPanel->setHeight(150);
    middleScreenPanel->setAnchor(gui::Anchor::Middle);
    middleScreenPanel->hide();

    middleScreenTitle = gui->create<gui::Text>(middleScreenPanel);
    middleScreenTitle->setText("GAME OVER");
    middleScreenTitle->setColor(Color::White());
    middleScreenTitle->setCharacterSize(45);
    middleScreenTitle->setAnchor(gui::Anchor::TopMiddle);
    middleScreenTitle->setPosition({0, 20});

    middleScreenSubtitle = gui->create<gui::Text>(middleScreenPanel);
    middleScreenSubtitle->setText("Press SPACE to retry");
    middleScreenSubtitle->setColor(Color::White());
    middleScreenSubtitle->setAnchor(gui::Anchor::BottomMiddle);
    middleScreenSubtitle->setPosition({0, -30});
    middleScreenSubtitle->setCharacterSize(20);

    ok = true;
    return true;
}

int Game::run() {
    if (!ok) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    Uint32 lastUpdate = SDL_GetTicks();

	while (!quit) {
		handleEvents();

        renderer.clear();
        this->RenderingHandler::notify(renderer);
        renderer.present();

        Uint32 currentTime = SDL_GetTicks();
        double dt = (currentTime - lastUpdate) / 1000.;

        if (!paused) {
            this->Subject<double>::notify(dt);
        }

        lastUpdate = currentTime;
	}

    return 0;
}

bool Game::isOk() const {
    return ok;
}

std::shared_ptr<Player> Game::getPlayer() const {
    return player;
}

void Game::addToScore(int scoreDelta) {
    score += scoreDelta;
    scoreText->setText("Score: " + toStringPrefixed(score));
}

int Game::getScore() const {
    return score;
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
                if (event.type == SDL_KEYUP
                 && event.key.keysym.sym == SDLK_p) {
                    togglePause();
                }

                if (!paused) {
                    KeyboardEventData data(
                            event.key.type == SDL_KEYUP
                            ? KeyboardEventData::Release
                            : KeyboardEventData::Press,
                            event.key.keysym.scancode,
                            event.key.keysym.sym
                    );
                    this->KeyboardHandler::notify(data);
                }

		        break;
		}

	}

}

void Game::togglePause() {
    paused = !paused;
    middleScreenPanel->setVisible(paused);

    if (paused) {
        middleScreenTitle->setText("PAUSED");
        middleScreenSubtitle->setText("Press P to unpause");
    }
}
