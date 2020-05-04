#include <SDL.h>
#include <iostream>
#include <atomic>
#include <thread>

#include "ParticleSystem/ParticleEmitter.hpp"

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

std::atomic<bool> quit;
ParticleSystem::ParticleEmitter emitter(100);

inline double getTime() {
    return SDL_GetTicks() / 1000.;
}

void particle_loop();

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized!\n"
                  << "SDL_Error: %s\n" << SDL_GetError()
                  << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Basic C SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created!\n"
                  << "SDL_Error: %s\n" << SDL_GetError()
                  << std::endl;
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        std::cerr << "Renderer could not be created!\n"
                  << "SDL_Error: %s\n" << SDL_GetError()
                  << std::endl;
        return 3;
    }

    emitter.setPosition({640, 360});
    emitter.particleInitializer.setColor({255, 0, 0, 255});
    emitter.particleInitializer.setDirectionRangeFirstEnd({-1, -1});
    emitter.particleInitializer.setDirectionRangeSecondEnd({1, -1});
    emitter.particleInitializer.setSpeed(100);
    emitter.particleInitializer.setMinLifetime(5.);
    emitter.particleInitializer.setMaxLifetime(10.);
    emitter.setDrawParticle([renderer](const ParticleSystem::BaseParticle& particle) {
        SDL_SetRenderDrawColor(
                renderer,
                particle.color.r(), particle.color.g(), particle.color.b(),
                particle.color.a()
        );
        SDL_RenderDrawPoint(
                renderer,
                particle.position.x(), particle.position.y()
        );
    });

    quit = false;

    std::thread particleThread(particle_loop);

    while (!quit) {
        SDL_Event e;
        SDL_WaitEvent(&e);

        if (e.type == SDL_QUIT) {
            quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);

        emitter.draw();

        SDL_RenderPresent(renderer);
    }

    particleThread.join();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void particle_loop() {
    double lastUpdate = getTime();
    while (!quit) {
        double dt = getTime() - lastUpdate;
        emitter.update(dt);
        lastUpdate = getTime();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
