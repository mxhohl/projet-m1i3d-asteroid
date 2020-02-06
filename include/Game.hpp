#ifndef GAME_HPP
#define GAME_HPP

#include "Renderer.hpp"
#include "Observer/Subject.hpp"

#include <SDL.h>

class Game : public Subject<Renderer> {
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
};

#endif // GAME_HPP
