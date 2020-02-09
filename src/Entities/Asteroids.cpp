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

#ifdef DEBUG
        renderer.setDrawColor({255, 0, 0, 255});
        renderer.draw(asteroid.getPosition(),
                      asteroid.getPosition() + asteroid.speed);
#endif
    }
}

void Asteroids::update(double& dt) {
    for (auto& asteroid : asteroids) {
        asteroid.move(asteroid.speed * dt);
        asteroid.rotate(asteroid.rotation_speed * float(dt));
    }
}
