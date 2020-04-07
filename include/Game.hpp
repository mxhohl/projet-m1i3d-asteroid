#ifndef GAME_HPP
#define GAME_HPP

#include <gui/Panel.hpp>
#include "gui/Text.hpp"
#include "gui/Gui.hpp"
#include "Physic/PhysicEngine.hpp"
#include "Rendering/Renderer.hpp"
#include "Observer/Subject.hpp"
#include "Entities/Player.hpp"
#include "Entities/Asteroids.hpp"

extern "C" {
#include <SDL.h>
};

class Game : public RenderingHandler,
             public KeyboardHandler,
             public UpdateHandler {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;
    void operator=(const Game&) = delete;

private:
    Game();

public:
    ~Game() override;

    bool init();
    int run();

    [[nodiscard]] bool isOk() const;

    void addToScore(int scoreDelta);

private:
    void handleEvents();

private:
    bool ok;
    bool quit;

    int score;

    SDL_Window* window;
    Renderer renderer;

private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Asteroids> asteroids;
    std::shared_ptr<PhysicEngine> physicEngine;
    std::shared_ptr<gui::Gui> gui;

    gui::Text::Ptr scoreText;

    gui::Panel::Ptr endTextPanel;
    gui::Text::Ptr endTextTitle;
    gui::Text::Ptr endTextSubtitle;
};

#endif // GAME_HPP
