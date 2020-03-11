#include <iostream>

#include "Physic/PhysicEngine.hpp"

#include "Rendering/Renderer.hpp"
#include "Physic/PhysicEntity.hpp"

PhysicEngine::PhysicEngine() : entityUidCounter(0) {};

void PhysicEngine::update(double& dt) {
    for (auto& entity : entities) {
        entity.first->physicUpdate(dt);
    }
    handleShotsCollisions();
}

void PhysicEngine::addEntity(const std::shared_ptr<PhysicEntity>& entity,
                             const Circle& bb) {
    entity->uid = entityUidCounter++;
    entities.emplace_back(entity, bb);
}

void PhysicEngine::removeEntity(const std::shared_ptr<PhysicEntity>& entity) {
    for (auto it = entities.begin(); it != entities.end();) {
        if (std::get<0>(*it)->uid == entity->uid) {
            entities.erase(it);
        } else {
            ++it;
        }
    }
}

void PhysicEngine::setShots(const std::shared_ptr<std::vector<Shot>>& sht) {
    shots = sht;
}

void PhysicEngine::handleShotsCollisions() {
    bool hit = false;
    for (auto it = shots->begin(); it != shots->end();) {
        for (auto& entityPoly : entities) {
            if (isPointInCircle(it->position, 
                                entityPoly.first->getPosition(), 
                                entityPoly.second)) {
                entityPoly.first->onCollide(CollisionType::WithShot);
                hit = true;
                break;
            }
        }

        if (hit) {
            it = shots->erase(it);
            hit = false;
        } else {
            ++it;
        }
    }
}

bool PhysicEngine::isPointInCircle(const Vec2f& point,
                                   const Vec2f& center,
                                   const Circle& circle) {
    return (center - point).sqrLength() < circle.getSqrRadius();
}
