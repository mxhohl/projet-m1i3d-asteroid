#include "Game.hpp"

#include "Settings.hpp"
#include "Logger.hpp"

#include <iostream>

Game::Game() : ok(false), quit(false), paused(false), gameOver(false), score(0),
               window(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        FATAL(sstr("SDL_Init Error: ", SDL_GetError()));
        ok = false;
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
        FATAL(sstr("SDL_CreateWindow Error: ", SDL_GetError()));
        ok = false;
        return;
    }

    renderer.create(window);

    if (!renderer.isOk()){
        SDL_DestroyWindow(window);
        ERROR("Unable to create renderer");
        ok = false;
        return;
    }


    physicEngine = std::make_shared<PhysicEngine>();
    this->UpdateHandler::addObserver(physicEngine);

    player = std::make_shared<Player>(physicEngine);
    this->RenderingHandler::addObserver(player);
    this->KeyboardHandler::addObserver(player);
    this->UpdateHandler::addObserver(player);


    asteroids = std::make_shared<Asteroids>(physicEngine);
    this->UpdateHandler::addObserver(asteroids);
    this->RenderingHandler::addObserver(asteroids);


    gui = std::make_shared<gui::Gui>();
    this->RenderingHandler::addObserver(gui);

    scoreText = gui->create<gui::Text>();
    scoreText->setPosition({10, 10});
    scoreText->setCharacterSize(20);
    scoreText->setColor(Color::White());

    middleScreenPanel = gui->create<gui::Panel>();
    middleScreenPanel->setColor({200, 200, 200, 70});
    middleScreenPanel->setWidth(300);
    middleScreenPanel->setHeight(150);
    middleScreenPanel->setAnchor(gui::Anchor::Middle);

    middleScreenTitle = gui->create<gui::Text>(middleScreenPanel);
    middleScreenTitle->setColor(Color::White());
    middleScreenTitle->setCharacterSize(45);
    middleScreenTitle->setAnchor(gui::Anchor::TopMiddle);
    middleScreenTitle->setPosition({0, 20});

    middleScreenSubtitle = gui->create<gui::Text>(middleScreenPanel);
    middleScreenSubtitle->setColor(Color::White());
    middleScreenSubtitle->setAnchor(gui::Anchor::BottomMiddle);
    middleScreenSubtitle->setPosition({0, -30});
    middleScreenSubtitle->setCharacterSize(20);

    setDefaultValues();

    ok = true;
}

Game::~Game() {
	SDL_Quit();
}

void Game::setDefaultValues() {
    Settings& settings = Settings::getInstance();

    physicEngine->setPlayer(player);
    player->setScale(5);
    player->setPosition({
        settings.getParameter<int>("window_width") / 2.f,
        settings.getParameter<int>("window_height") / 2.f
    });

    scoreText->setText("Score: 00000");
    middleScreenPanel->hide();
    middleScreenTitle->setText("Lorem ispum");
    middleScreenSubtitle->setText("Dolor sit amet");

    score = 0;
    paused = false;
    gameOver = false;
}

void Game::startGame() {
    Settings& settings = Settings::getInstance();

    asteroids->reset();
    player->reset();
    physicEngine->reset();

    setDefaultValues();

    asteroids->spawnAsteroids(
            settings.getParameter<unsigned>("init_asteroid_count")
    );
}

int Game::run() {
    if (!ok) {
        ERROR("Unable to run game which is not ok");
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

        if (!paused && !gameOver) {
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

void Game::endGame() {
    gameOver = true;

    middleScreenPanel->show();
    middleScreenTitle->setText("GAME OVER");
    middleScreenSubtitle->setText("Press SPACE to retry");
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

                if (gameOver
                 && event.type == SDL_KEYUP
                 && event.key.keysym.sym == SDLK_SPACE) {
                    startGame();
                }

                if (!paused && !gameOver) {
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
