#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Physic/PhysicEntity.hpp"
#include "Types/Vec2.hpp"
#include "Types/Color.hpp"
#include "Rendering/Polygon.hpp"

#include <random>

class Asteroid : public PhysicEntity {
private:
    static constexpr float BASE_RADIUS = 1.f;

public:
    Asteroid();
    static Asteroid random();

    void onCollide(PhysicEngine::CollisionType collisionType) override;

    [[nodiscard]] const Color& getColor() const;
    void setColor(const Color& col);

    float getRadius() const;
    int getSize() const;
    void setSize(int s);

    Circle getCircle() const;

private:
    void generatePolygon();

private:
    float rotation_speed;
    int size;
    Color color;
};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
