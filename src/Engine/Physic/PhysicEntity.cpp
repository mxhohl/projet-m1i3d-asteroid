#include "Engine/Physic/PhysicEntity.hpp"

#include <utility>

PhysicEntity::PhysicEntity() : PhysicEntity({0, 0}, {0, 0}, 500) {}

PhysicEntity::PhysicEntity(Vec2f  acceleration,
                           Vec2f  speed,
                           float maxSpeed) :
        acceleration(std::move(acceleration)),
        speed(std::move(speed)),
        minSpeed(0),
        maxSpeed(maxSpeed),
        uid(0) {}

void PhysicEntity::physicUpdate(double dt) {
    speed += acceleration * dt;

    if (speed.length() > maxSpeed) {
        speed.normalize();
        speed *= maxSpeed;
    } else if (minSpeed != 0 && speed.length() < minSpeed) {
        speed.normalize();
        speed *= minSpeed;
    }

    setPosition(getPosition() + speed * dt);
}

const Vec2f& PhysicEntity::getAcceleration() const {
    return acceleration;
}

void PhysicEntity::setAcceleration(const Vec2f& acc) {
    acceleration = acc;
}

const Vec2f& PhysicEntity::getSpeed() const {
    return speed;
}

void PhysicEntity::setSpeed(const Vec2f& spd) {
    speed = spd;
}

float PhysicEntity::getMaxSpeed() const {
    return maxSpeed;
}

void PhysicEntity::setMaxSpeed(float maxSpd) {
    maxSpeed = maxSpd;
}

float PhysicEntity::getMinSpeed() const {
    return minSpeed;
}

void PhysicEntity::setMinSpeed(float minSpd) {
    minSpeed = minSpd;
}

uint32_t PhysicEntity::getUid() const {
    return uid;
}
