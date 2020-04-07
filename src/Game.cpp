#include "Game.hpp"

#include "Settings.hpp"

#include <iostream>

Game::Game() : ok(false), quit(false), score(0), window(nullptr) {
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

    asteroids = std::make_shared<Asteroids>(10, physicEngine);
    this->UpdateHandler::addObserver(asteroids);
    this->RenderingHandler::addObserver(asteroids);


    gui = std::make_shared<gui::Gui>();
    this->RenderingHandler::addObserver(gui);

    scoreText = gui->create<gui::Text>();
    scoreText->setText("Score: 00000");
    scoreText->setPosition({10, 10});
    scoreText->setScale(0.7);
    scoreText->setColor(Color::White());

    endTextPanel = gui->create<gui::Panel>();
    endTextPanel->setColor({200, 200, 200, 50});
    endTextPanel->setWidth(300);
    endTextPanel->setHeight(150);
    endTextPanel->setPosition(Vec2f(
            static_cast<float>(settings.getParameter<int>("window_width")) / 2.f - 150.f,
            static_cast<float>(settings.getParameter<int>("window_height")) / 2.f - 75.f
    ));

    endTextTitle = gui->create<gui::Text>();
    endTextTitle->setText("GAME OVER");
    endTextTitle->setColor(Color::White());
    endTextTitle->setScale(1.35);
    endTextTitle->setPosition(Vec2f{
        endTextPanel->getPosition().x() + (endTextPanel->getWidth() - endTextTitle->getWidth() * endTextTitle->getScale().x()) / 2.f,
        endTextPanel->getPosition().y() + (endTextPanel->getHeight() - endTextTitle->getHeight() * endTextTitle->getScale().y()) / 2.f - 30.f
    });

    endTextSubtitle = gui->create<gui::Text>();
    endTextSubtitle->setText("Press SPACE to retry");
    endTextSubtitle->setScale(0.7);
    endTextSubtitle->setColor(Color::White());
    endTextSubtitle->setPosition(Vec2f{
        endTextPanel->getPosition().x() + (endTextPanel->getWidth() - endTextSubtitle->getWidth() * endTextSubtitle->getScale().x()) / 2.f,
        endTextPanel->getPosition().y() + (endTextPanel->getHeight() - endTextSubtitle->getHeight() * endTextSubtitle->getScale().y()) / 2.f + 30.f
    });

    endTextPanel->addEntity(endTextTitle, gui::Anchor::Middle);
    endTextPanel->addEntity(endTextSubtitle, gui::Anchor::Middle);
    endTextPanel->hide();

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
                if (event.type == SDL_KEYUP
                    && event.key.keysym.sym == SDLK_SPACE) {
                    endTextPanel->toggleVisibility();
                } else {
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

void Game::addToScore(int scoreDelta) {
    score += scoreDelta;
    scoreText->setText("Score: " + toStringPrefixed(score));
}
