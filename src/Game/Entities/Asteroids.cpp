#include "Game/Entities/Asteroids.hpp"

#include <utility>
#include <iostream>

#include "Game/Game.hpp"

Asteroids::Asteroids(std::shared_ptr<engine::PhysicEngine> physicEngine)  :
        physicEngine(std::move(physicEngine)),
        asteroidSpawnTimer(0) {}


Asteroids::~Asteroids() = default;

void Asteroids::update(engine::Renderer& renderer) {
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

void Asteroids::update(double dt) {
    int scoreDelta = handleExplosions();
    if (scoreDelta > 0) {
        Game::getInstance().addToScore(scoreDelta);
    }

    handleAsteroidsSpawn(dt);
}

void Asteroids::spawnAsteroids(size_t count) {
    for (size_t i = 0; i < count; ++i) {
        spawnAsteroid();
    }
}

void Asteroids::reset() {
    asteroids.clear();
}

void Asteroids::spawnAsteroid() {
    auto asteroid = std::make_shared<Asteroid>(Asteroid::random(
            randomContext,
            Game::getInstance().getPlayer()
    ));
    auto circle = asteroid->getCircle();
    circle.setRadius(circle.getRadius() * asteroid->getScale().x());
    physicEngine->addEntity(asteroid, circle);
    asteroids.push_back(asteroid);
}

int Asteroids::handleExplosions() {
    int scoreDelta = 0;
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        if ((*it)->exploding) {
            ++scoreDelta;

            if ((*it)->size > 1) {
                engine::Circle circle((*it)->getCircle().getRadius() * 0.8f);
                const engine::Polygon& points = circle.getPolygon(3);
                auto transform = (*it)->getTransformMatrix();
                for (int i = 0; i < 3; ++i) {
                    auto newAsteroid = Asteroid::fromExplosion(
                            *it,
                            randomContext,
                            transform.transformPoint(points[i])
                    );

                    auto newAsteroidCircle = newAsteroid->getCircle();
                    newAsteroidCircle.setRadius(newAsteroidCircle.getRadius()
                                                * newAsteroid->getScale().x());

                    physicEngine->addEntity(newAsteroid, newAsteroidCircle);

                    it = asteroids.insert(it, newAsteroid);
                    ++it;
                }
            }

            physicEngine->removeEntity(*it);
            it = asteroids.erase(it);
        } else {
            ++it;
        }
    }
    return scoreDelta;
}

void Asteroids::handleAsteroidsSpawn(double dt) {
    asteroidSpawnTimer += dt;

    const auto currentSpawnRate = ASTEROID_BASE_SPAWN_RATE
            * (1 + Game::getInstance().getScore() / 30.);

    while (asteroidSpawnTimer >= currentSpawnRate) {
        asteroidSpawnTimer -= currentSpawnRate;
        spawnAsteroid();
    }
}
