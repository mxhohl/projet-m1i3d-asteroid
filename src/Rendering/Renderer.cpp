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

void Renderer::drawPolygon(const Polygon &polygon) {
    for (size_t i = 0; i < polygon.pointsCount(); ++i) {
        Vec2f p1 = polygon.getPointInWorldPos(i);
        Vec2f p2 = polygon.getPointInWorldPos((i + 1) % polygon.pointsCount());
        SDL_RenderDrawLineF(renderer, p1.x(), p1.y(), p2.x(), p2.y());
    }
}

void Renderer::drawLine(const Vec2f& start, const Vec2f& end) {
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());
}

void Renderer::drawLines(const std::vector<Vec2f>& points) {
    for (size_t i = 0; i < points.size(); i += 2) {
        SDL_RenderDrawLineF(
                renderer,
                points[i].x(), points[i].y(),
                points[i + 1].x(), points[i + 1].y()
        );
    }
}

void Renderer::drawPoint(const Vec2f& point) {
    SDL_RenderDrawPoint(renderer, point.x(), point.y());
}

void Renderer::drawPoints(const std::vector<Vec2f>& points) {
    for (const auto& point : points) {
        SDL_RenderDrawPoint(renderer, point.x(), point.y());
    }
}
