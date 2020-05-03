#ifndef GAME_HPP
#define GAME_HPP

#include "Engine/gui/Entities/Panel.hpp"
#include "Engine/gui/Entities/Text.hpp"
#include "Engine/gui/Gui.hpp"
#include "Engine/Physic/PhysicEngine.hpp"
#include "Engine/Rendering/Renderer.hpp"
#include "Engine/Observer/Subject.hpp"
#include "Game/Entities/Player.hpp"
#include "Game/Entities/Asteroids.hpp"

extern "C" {
#include <SDL.h>
};

class Game : public engine::RenderingHandler,
             public engine::KeyboardHandler,
             public engine::UpdateHandler {
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

    int run();

    [[nodiscard]] bool isOk() const;

    [[nodiscard]] std::shared_ptr<Player> getPlayer() const;
    void addToScore(int scoreDelta);
    [[nodiscard]] int getScore() const;

    void endGame();
    void startGame();

private:
    void setDefaultValues();

    void handleEvents();
    void togglePause();

private:
    bool ok;
    bool quit;
    bool paused;
    bool gameOver;

    int score;

    SDL_Window* window;
    engine::Renderer renderer;

private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Asteroids> asteroids;
    std::shared_ptr<engine::PhysicEngine> physicEngine;
    std::shared_ptr<engine::gui::Gui> gui;

    engine::gui::Text::Ptr scoreText;
    engine::gui::Text::Ptr refreshTimeText;

    engine::gui::Panel::Ptr middleScreenPanel;
    engine::gui::Text::Ptr middleScreenTitle;
    engine::gui::Text::Ptr middleScreenSubtitle;
};

#endif // GAME_HPP
