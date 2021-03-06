#include "Game/Game.hpp"

#include "Engine/Settings.hpp"
#include "Engine/Logger.hpp"

#include <iostream>

Game::Game() : ok(false), quit(false), paused(false), gameOver(false), score(0),
               window(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        FATAL(sstr("SDL_Init Error: ", SDL_GetError()));
        ok = false;
    }

    auto& settings = engine::Settings::getInstance();

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


    physicEngine = std::make_shared<engine::PhysicEngine>();
    this->engine::UpdateHandler::addObserver(physicEngine);

    player = std::make_shared<Player>(physicEngine);
    this->engine::RenderingHandler::addObserver(player);
    this->engine::KeyboardHandler::addObserver(player);
    this->engine::UpdateHandler::addObserver(player);


    asteroids = std::make_shared<Asteroids>(physicEngine);
    this->engine::UpdateHandler::addObserver(asteroids);
    this->engine::RenderingHandler::addObserver(asteroids);


    gui = std::make_shared<engine::gui::Gui>();
    this->engine::RenderingHandler::addObserver(gui);

    scoreText = gui->create<engine::gui::Text>();
    scoreText->setPosition({10, 10});
    scoreText->setCharacterSize(20);
    scoreText->setColor(engine::Color::White());

    refreshTimeText = gui->create<engine::gui::Text>();
    refreshTimeText->setPosition({-2, 2});
    refreshTimeText->setAnchor(engine::gui::Anchor::TopRight);
    refreshTimeText->setColor({0, 150, 0, 200});
    refreshTimeText->setCharacterSize(10);
    refreshTimeText->setText("1000 ms");

    middleScreenPanel = gui->create<engine::gui::Panel>();
    middleScreenPanel->setColor({200, 200, 200, 70});
    middleScreenPanel->setWidth(300);
    middleScreenPanel->setHeight(150);
    middleScreenPanel->setAnchor(engine::gui::Anchor::Middle);

    middleScreenTitle = gui->create<engine::gui::Text>(middleScreenPanel);
    middleScreenTitle->setColor(engine::Color::White());
    middleScreenTitle->setCharacterSize(45);
    middleScreenTitle->setAnchor(engine::gui::Anchor::TopMiddle);
    middleScreenTitle->setPosition({0, 20});

    middleScreenSubtitle = gui->create<engine::gui::Text>(middleScreenPanel);
    middleScreenSubtitle->setColor(engine::Color::White());
    middleScreenSubtitle->setAnchor(engine::gui::Anchor::BottomMiddle);
    middleScreenSubtitle->setPosition({0, -30});
    middleScreenSubtitle->setCharacterSize(20);

    setDefaultValues();

    ok = true;
}

Game::~Game() {
	SDL_Quit();
}

void Game::setDefaultValues() {
    auto& settings = engine::Settings::getInstance();

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
    auto& settings = engine::Settings::getInstance();

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
        this->engine::RenderingHandler::notify(renderer);
        renderer.present();

        Uint32 currentTime = SDL_GetTicks();
        double dtms = currentTime - lastUpdate;
        double dt = dtms / 1000.;

        refreshTimeText->setText(sstr(dtms, " ms"));

        if (!paused && !gameOver) {
            this->engine::Subject<double>::notify(dt);
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
                    engine::KeyboardEventData data(
                            event.key.type == SDL_KEYUP
                            ? engine::KeyboardEventData::Release
                            : engine::KeyboardEventData::Press,
                            event.key.keysym.scancode,
                            event.key.keysym.sym
                    );
                    this->engine::KeyboardHandler::notify(data);
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
