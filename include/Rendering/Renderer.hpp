#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Types/Vec2.hpp"
#include "Types/Mat3.hpp"
#include "Types/Color.hpp"
#include "Types/Rect.hpp"
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
    [[nodiscard]] bool isOk() const;

    void setDrawColor(const Color& color);
    void clear(const Color& color = {0, 0, 0, 255});
    void present();

    void draw(const Polygon& polygon,
              const Mat3f& transform = Mat3f::identity());
    void draw(const Vec2f& start, const Vec2f& end,
              const Mat3f& transform = Mat3f::identity());
    void draw(const Vec2f& point,
              const Mat3f& transform = Mat3f::identity());
    void draw(const RectF& rect,
              bool fill,
              const Mat3f& transform = Mat3f::identity());

private:
    SDL_Renderer* renderer;
    Color currentColor;
};

#endif // RENDERER_HPP
