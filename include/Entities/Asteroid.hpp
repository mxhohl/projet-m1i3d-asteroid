#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Physic/PhysicEntity.hpp"
#include "Types/Vec2.hpp"
#include "Types/Color.hpp"
#include "Rendering/Polygon.hpp"

#include <random>

class Asteroid : public PhysicEntity {
    friend class Asteroids;

private:
    static constexpr float BASE_RADIUS = 10.f;

public:
    Asteroid();
    static Asteroid random();

    void onCollide(PhysicEngine::CollisionType collisionType) override;

    [[nodiscard]] const Color& getColor() const;
    void setColor(const Color& col);

    [[nodiscard]] float getRadius() const;
    [[nodiscard]] int getSize() const;
    void setSize(int s);

    [[nodiscard]] Circle getCircle() const;

private:
    float rotation_speed;
    int size;
    Color color;

    bool exploding;

};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
