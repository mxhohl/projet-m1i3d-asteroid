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
        auto circle = asteroid->getCircle();
        circle.setRadius(circle.getRadius() * asteroid->getScale().x());
        physicEngine->addEntity(asteroid, circle);
        asteroids.push_back(asteroid);
    }
}

void Asteroids::update(Renderer& renderer) {
    for (auto& asteroid : asteroids) {
        renderer.setDrawColor(asteroid->getColor());
        renderer.draw(asteroid->getCircle(), asteroid->getTransformMatrix());

#ifdef DEBUG
        renderer.setDrawColor({255, 0, 0, 255});
        renderer.draw(asteroid->getPosition(),
                      asteroid->getPosition() + asteroid->getSpeed());
#endif
    }
}

void Asteroids::update([[maybe_unused]] double& t) {
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        if ((*it)->exploding) {
            if ((*it)->size == 1) {
                it = asteroids.erase(it);
                continue;
            } else {
                Circle circle((*it)->getCircle().getRadius() * 0.8f);
                const Polygon& points = circle.getPolygon(3);
                auto transform = (*it)->getTransformMatrix();
                for (int i = 0; i < 3; ++i) {
                    auto newAsteroid = std::make_shared<Asteroid>();
                    newAsteroid->size = (*it)->size - 1;
                    newAsteroid->color = (*it)->color;
                    newAsteroid->rotation_speed = (*it)->rotation_speed;
                    
                    newAsteroid->setScale((*it)->getScale());
                    newAsteroid->setRotation((*it)->getRotation());

                    newAsteroid->setPosition(transform.transformPoint(points[i]));

                    newAsteroid->setSpeed(
                        (*it)->getSpeed() 
                        + (newAsteroid->getPosition() - (*it)->getPosition())
                    );

                    auto circle = newAsteroid->getCircle();
                    circle.setRadius(circle.getRadius() 
                                     * newAsteroid->getScale().x());
                    physicEngine->addEntity(newAsteroid, circle);

                    it = asteroids.insert(it, newAsteroid);
                    ++it;
                }

                physicEngine->removeEntity(*it);
                it = asteroids.erase(it);
            }
        }

        ++it;
    }
}
