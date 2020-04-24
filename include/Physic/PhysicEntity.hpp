#ifndef PROJETPROGAVANCEE_PHYSICENTITY_HPP
#define PROJETPROGAVANCEE_PHYSICENTITY_HPP

#include "Transformable.hpp"
#include "PhysicEngine.hpp"

class PhysicEntity : public Transformable {
    friend class PhysicEngine;

public:
    PhysicEntity();
    PhysicEntity(Vec2f  acceleration, Vec2f  speed, float maxSpeed);

    friend bool operator==(const PhysicEntity& e1, const PhysicEntity& e2) {
        return e1.uid == e2.uid;
    }

    friend bool operator!=(const PhysicEntity& e1, const PhysicEntity& e2) {
        return e1.uid != e2.uid;
    }

    virtual void onCollide(PhysicEngine::CollisionType collisionType,
                           Vec2f position) = 0;
    void physicUpdate(double dt);

    [[nodiscard]] const Vec2f& getAcceleration() const;
    void setAcceleration(const Vec2f& acc);

    [[nodiscard]] const Vec2f& getSpeed() const;
    void setSpeed(const Vec2f& spd);

    [[nodiscard]] float getMaxSpeed() const;
    void setMaxSpeed(float maxSpd);

    [[nodiscard]] float getMinSpeed() const;
    void setMinSpeed(float minSpd);

    [[nodiscard]] uint32_t getUid() const;

private:
    Vec2f acceleration;
    Vec2f speed;

    float minSpeed;
    float maxSpeed;

private:
    uint32_t uid;
};

#endif //PROJETPROGAVANCEE_PHYSICENTITY_HPP
