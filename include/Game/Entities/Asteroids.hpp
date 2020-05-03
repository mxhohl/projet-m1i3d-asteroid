#ifndef PROJETPROGAVANCEE_ASTEROIDS_HPP
#define PROJETPROGAVANCEE_ASTEROIDS_HPP

#include "Engine/Rendering/Renderer.hpp"
#include "Engine/Observer/Observer.hpp"
#include "Engine/Observer/Subject.hpp"
#include "Engine/Rendering/Polygon.hpp"
#include "Asteroid.hpp"

#include <vector>

class Asteroids : public engine::Renderable,
                  public engine::Updatable {
public:
    static constexpr double ASTEROID_BASE_SPAWN_RATE = 3.;

public:
    explicit Asteroids(std::shared_ptr<engine::PhysicEngine>  physicEngine);
    ~Asteroids() override;

    void update(engine::Renderer& renderer) override;
    void update(double dt) override;

    void reset();
    void spawnAsteroids(size_t count);

private:
    void spawnAsteroid();

    int handleExplosions();
    void handleAsteroidsSpawn(double dt);

private:
    std::vector<std::shared_ptr<Asteroid>> asteroids;
    std::shared_ptr<engine::PhysicEngine> physicEngine;

    double asteroidSpawnTimer;
};

#endif //PROJETPROGAVANCEE_ASTEROIDS_HPP
