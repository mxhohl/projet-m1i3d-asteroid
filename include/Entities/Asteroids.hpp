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
    Asteroids();
    explicit Asteroids(size_t count);

    void update(Renderer& renderer) override;
    void update(double& dt) override;

private:
    std::vector<Asteroid> asteroids;
};

#endif //PROJETPROGAVANCEE_ASTEROIDS_HPP
