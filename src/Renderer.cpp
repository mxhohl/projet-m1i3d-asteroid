#include "Renderer.hpp"

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

void Renderer::drawLine(Vec2f start, Vec2f end) {
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());
}

void Renderer::drawLines(std::vector<Vec2f> points) {
    for (size_t i = 0; i < points.size(); i += 2) {
        SDL_RenderDrawLineF(
                renderer,
                points[i].x(), points[i].y(),
                points[i + 1].x(), points[i + 1].y()
        );
    }
}
