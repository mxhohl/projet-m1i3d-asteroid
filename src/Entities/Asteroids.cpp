#include "Entities/Asteroids.hpp"

#include <utility>
#include <iostream>

Asteroids::Asteroids(const std::shared_ptr<PhysicEngine>& physicEngine) :
        Asteroids(0, physicEngine) {}

Asteroids::Asteroids(size_t count,
                     const std::shared_ptr<PhysicEngine>& physicEngine) :
        physicEngine(physicEngine) {

    for (size_t i = 0; i < count; ++i) {
        auto asteroid = std::make_shared<Asteroid>(Asteroid::random());
        physicEngine->addEntity(asteroid, asteroid->getPolygon());
        asteroids.push_back(asteroid);
    }
}

void Asteroids::update(Renderer& renderer) {
    for (auto& asteroid : asteroids) {
        renderer.setDrawColor(asteroid->getColor());
        renderer.draw(asteroid->getPolygon(), asteroid->getTransformMatrix());

#ifdef DEBUG
        renderer.setDrawColor({255, 0, 0, 255});
        renderer.draw(asteroid->getPosition(),
                      asteroid->getPosition() + asteroid->getSpeed());
#endif
    }
}
