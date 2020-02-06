#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>

class Renderer {
public:
    Renderer();
    explicit Renderer(SDL_Window* window);

    void create(SDL_Window* window);
    bool isOk() const;

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255); /* TODO: use Color class */
    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255); /* TODO: use color class */
    void present();

    void drawLine(Vec2f start, Vec2f end);
    void drawLines(std::vector<Vec2f> points);

private:
    SDL_Renderer* renderer;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
};

#endif // RENDERER_HPP
