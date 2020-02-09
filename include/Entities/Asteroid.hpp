#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Transformable.hpp"
#include "Types/Vec2.hpp"
#include "Types/Color.hpp"
#include "Rendering/Polygon.hpp"

#include <random>

struct Asteroid : public Transformable {
    Asteroid();
    explicit Asteroid(Vec2f speed);

    static Asteroid random();

    Vec2f speed;
    float rotation_speed;
    Polygon polygon;
    Color color;

    void generateShape(std::default_random_engine generator);
};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
