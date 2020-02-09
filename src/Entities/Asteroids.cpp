#include "Entities/Asteroids.hpp"

#include <utility>

Asteroids::Asteroids() : Asteroids(0) {}

Asteroids::Asteroids(size_t count) {
    for (size_t i = 0; i < count; ++i) {
        asteroids.push_back(Asteroid::random());
    }
}

void Asteroids::update(Renderer& renderer) {
    for (auto& asteroid : asteroids) {
        renderer.setDrawColor(asteroid.color);
        renderer.draw(asteroid.polygon, asteroid.getTransformMatrix());
    }
}

void Asteroids::update(double& dt) {
    for (auto& asteroid : asteroids) {
        asteroid.move(asteroid.speed * dt);
        asteroid.rotate(asteroid.rotation_speed * dt);
    }
}
