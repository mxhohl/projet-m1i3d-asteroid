#ifndef GAME_HPP
#define GAME_HPP

#include "gui/Text.hpp"
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
             public UpdateHandler,
             public ScoreObserver {
public:
    Game();
    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;

    ~Game();

    int run();

    [[nodiscard]] bool isOk() const;

    void update(int& scoreDelta) override;

private:
    void handleEvents();

private:
    bool ok;
    bool quit;

    int score;

    SDL_Window* window;
    Renderer renderer;
    std::shared_ptr<PhysicEngine> physicEngine;

private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Asteroids> asteroids;
    std::shared_ptr<gui::Text> scoreText;
};

#endif // GAME_HPP
