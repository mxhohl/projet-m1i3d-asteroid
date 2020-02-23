#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Physic/PhysicEntity.hpp"
#include "Types/Vec2.hpp"
#include "Types/Color.hpp"
#include "Rendering/Polygon.hpp"

#include <random>

class Asteroid : public PhysicEntity {
public:
    Asteroid();
    static Asteroid random();

    void onCollide(PhysicEngine::CollisionType collisionType) override;

    void generatePolygon(std::default_random_engine generator);
    [[nodiscard]] Polygon getPolygon() const;

    [[nodiscard]] const Color& getColor() const;
    void setColor(const Color& col);

private:
    float rotation_speed;
    Polygon polygon;
    Color color;
};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
