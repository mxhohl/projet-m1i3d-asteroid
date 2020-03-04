#ifndef PROJETPROGAVANCEE_ASTEROIDS_HPP
#define PROJETPROGAVANCEE_ASTEROIDS_HPP

#include "Rendering/Renderer.hpp"
#include "Observer/Observer.hpp"
#include "Rendering/Polygon.hpp"
#include "Asteroid.hpp"

#include <vector>

class Asteroids : public Renderable,
                  public Updatable {
public:
    explicit Asteroids(const std::shared_ptr<PhysicEngine>& physicEngine);
    Asteroids(size_t count,
              const std::shared_ptr<PhysicEngine>& physicEngine);

    void update(Renderer& renderer) override;
    void update(double& t) override;

private:
    std::vector<std::shared_ptr<Asteroid>> asteroids;
    std::shared_ptr<PhysicEngine> physicEngine;
};

#endif //PROJETPROGAVANCEE_ASTEROIDS_HPP
