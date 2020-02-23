#include "Rendering/Renderer.hpp"

#include <iostream>

Renderer::Renderer() : renderer(nullptr) {}

Renderer::Renderer(SDL_Window* window) {
    create(window);
}

void Renderer::create(SDL_Window *window) {
    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error:"
                  << SDL_GetError()
                  << std::endl;
        return;
    }
}

bool Renderer::isOk() const {
    return renderer != nullptr;
}

void Renderer::setDrawColor(const Color& color) {
    currentColor = color;
    SDL_SetRenderDrawColor(
            renderer,
            color.r(), color.g(), color.b(),
            color.a()
    );
}

void Renderer::clear(const Color& color) {
    SDL_SetRenderDrawColor(
            renderer,
            color.r(), color.g(), color.b(), color.a()
    );
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(
            renderer,
            currentColor.r(), currentColor.g(), currentColor.b(),
            currentColor.a()
    );
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::draw(const Polygon &polygon, const Mat3f& transform) {
    for (size_t i = 0; i < polygon.pointsCount(); ++i) {
        Vec2f p1 = transform.transformPoint(polygon[i]);
        Vec2f p2 = transform.transformPoint(
                polygon[(i + 1) % polygon.pointsCount()]
        );

        SDL_RenderDrawLineF(renderer, p1.x(), p1.y(), p2.x(), p2.y());
    }
#ifdef DEBUG
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    draw(polygon.getCentroid(), transform);
    SDL_SetRenderDrawColor(
            renderer,
            currentColor.r(), currentColor.g(), currentColor.b(),
            currentColor.a()
    );
#endif
}

void Renderer::draw(const Vec2f& start, const Vec2f& end,
                    const Mat3f& transform) {
    const Vec2f realStart = transform.transformPoint(start);
    const Vec2f realEnd = transform.transformPoint(end);
    SDL_RenderDrawLineF(renderer,
                        realStart.x(), realStart.y(),
                        realEnd.x(), realEnd.y());
}

void Renderer::draw(const Vec2f& point, const Mat3f& transform) {
    const Vec2f p = transform.transformPoint(point);
    SDL_RenderDrawPoint(renderer, p.x(), p.y());
}

void Renderer::draw(const RectF& rect, const Mat3f& transform) {
    const Vec2f tl = transform.transformPoint(
            rect.position()
    );
    const Vec2f tr = transform.transformPoint(
            rect.position() + Vec2f(rect.width(), 0)
    );
    const Vec2f br = transform.transformPoint(
            rect.position() + rect.size()
    );
    const Vec2f bl = transform.transformPoint(
            rect.position() + Vec2f(0, rect.height())
    );

    draw(tl, tr, transform);
    draw(tr, br, transform);
    draw(br, bl, transform);
    draw(bl, tl, transform);
}
