#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Types/Vec2.hpp"
#include "Types/Color.hpp"
#include "Polygon.hpp"

#include <vector>
extern "C" {
#include <SDL.h>
};

class Renderer {
public:
    Renderer();
    explicit Renderer(SDL_Window* window);

    void create(SDL_Window* window);
    bool isOk() const;

    void setDrawColor(const Color& color);
    void clear(const Color& color = {0, 0, 0, 255});
    void present();

    void drawPolygon(const Polygon& polygon);
    void drawLine(const Vec2f& start, const Vec2f& end);
    void drawLines(const std::vector<Vec2f>& points);
    void drawPoint(const Vec2f& point);
    void drawPoints(const std::vector<Vec2f>& points);
    /* TODO: drawRect and drawFillRect */

private:
    SDL_Renderer* renderer;
    Color currentColor;
};

#endif // RENDERER_HPP
