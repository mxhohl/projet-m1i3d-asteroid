#ifndef GAME_HPP
#define GAME_HPP

#include "Rendering/Renderer.hpp"
#include "Observer/Subject.hpp"
#include "Entities/Player.hpp"
#include "Entities/Asteroids.hpp"

extern "C" {
#include <SDL.h>
};

class Game : public Subject<Renderer>,
             public Subject<KeyboardEventData>,
             public Subject<double> {
public:
    Game();
    Game(const Game& copy) = delete;
    Game(Game&& move) = delete;

    ~Game();

    int run();

    bool isOk() const;

private:
    void handleEvents();

private:
    bool ok;
    bool quit;

    SDL_Window* window;
    Renderer renderer;

private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Asteroids> asteroids;
};

#endif // GAME_HPP
