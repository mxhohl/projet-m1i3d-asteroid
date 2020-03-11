#ifndef PROJETPROGAVANCEE_PHYSICENTITY_HPP
#define PROJETPROGAVANCEE_PHYSICENTITY_HPP

#include "Transformable.hpp"
#include "PhysicEngine.hpp"

class PhysicEntity : public Transformable {
    friend class PhysicEngine;

public:
    PhysicEntity();
    PhysicEntity(Vec2f  acceleration, Vec2f  speed, float maxSpeed);

    virtual void onCollide(PhysicEngine::CollisionType collisionType) = 0;
    void physicUpdate(double dt);

    [[nodiscard]] const Vec2f& getAcceleration() const;
    void setAcceleration(const Vec2f& acc);

    [[nodiscard]] const Vec2f& getSpeed() const;
    void setSpeed(const Vec2f& spd);

    [[nodiscard]] float getMaxSpeed() const;
    void setMaxSpeed(float maxSpd);

    uint32_t getUid() const;

private:
    Vec2f acceleration;
    Vec2f speed;

    float maxSpeed;

private:
    uint32_t uid;
};

#endif //PROJETPROGAVANCEE_PHYSICENTITY_HPP
