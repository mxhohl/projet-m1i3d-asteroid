#ifndef PROJETPROGAVANCEE_ASTEROIDS_HPP
#define PROJETPROGAVANCEE_ASTEROIDS_HPP

#include "Rendering/Renderer.hpp"
#include "Observer/Observer.hpp"
#include "Observer/Subject.hpp"
#include "Rendering/Polygon.hpp"
#include "Asteroid.hpp"

#include <vector>

class Asteroids : public Renderable,
                  public Updatable {
public:
    static constexpr double ASTEROID_BASE_SPAWN_RATE = 3.;

public:
    explicit Asteroids(const std::shared_ptr<PhysicEngine>& physicEngine);
    Asteroids(size_t count,
              const std::shared_ptr<PhysicEngine>& physicEngine);
    ~Asteroids() override;

    void update(Renderer& renderer) override;
    void update(double dt) override;

private:
    void spawnAsteroid();

    int handleExplosions();
    void handleAsteroidsSpawn(double dt);

private:
    std::vector<std::shared_ptr<Asteroid>> asteroids;
    std::shared_ptr<PhysicEngine> physicEngine;

    double asteroidSpawnTimer;
};

#endif //PROJETPROGAVANCEE_ASTEROIDS_HPP
