#include <iostream>

#include "Physic/PhysicEngine.hpp"

#include "Rendering/Renderer.hpp"
#include "Physic/PhysicEntity.hpp"

PhysicEngine::PhysicEngine() = default;

void PhysicEngine::update(double& dt) {
    for (auto& entity : entities) {
        entity.first->physicUpdate(dt);
    }
    handleShotsCollisions();
}

void PhysicEngine::addEntity(const std::shared_ptr<PhysicEntity>& entity,
                             const Circle& bb) {
    entities.emplace_back(entity, bb);
}

void PhysicEngine::setShots(const std::shared_ptr<std::vector<Shot>>& sht) {
    shots = sht;
}

void PhysicEngine::handleShotsCollisions() {
    for (auto it = shots->begin(); it != shots->end(); ++it) {
        for (auto& entityPoly : entities) {
            if (isPointInCircle(it->position, 
                                entityPoly.first->getPosition(), 
                                entityPoly.second)) {
                entityPoly.first->onCollide(CollisionType::WithShot);
                /* TODO: peut-être bogué */
                shots->erase(it);
            }
        }
    }
}

bool PhysicEngine::isPointInCircle(const Vec2f& point,
                                   const Vec2f& center,
                                   const Circle& circle) {
    return (center - point).sqrLength() < circle.getSqrRadius();
}
