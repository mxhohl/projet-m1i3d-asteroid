#include <iostream>

#include "Engine/Physic/PhysicEngine.hpp"
#include "Engine/Physic/PhysicEntity.hpp"
#include "Game/Entities/Player.hpp"

PhysicEngine::PhysicEngine() : entityUidCounter(0) {}

void PhysicEngine::update(double dt) {
    for (auto& entity : entities) {
        entity.first->physicUpdate(dt);
    }

    handleShotsCollisions();
    handleEntitiesCollisions();
    if (player) {
        handlePlayerCollisions();
    }
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

void PhysicEngine::setPlayer(const std::shared_ptr<Player> &p) {
    player = p;
}

void PhysicEngine::reset() {
    entities.clear();
}

void PhysicEngine::handleShotsCollisions() {
    bool hit = false;
    for (auto it = shots->begin(); it != shots->end();) {
        for (auto& entityPoly : entities) {
            if (isPointInCircle(it->position, 
                                entityPoly.first->getPosition(), 
                                entityPoly.second)) {
                entityPoly.first->onCollide(CollisionType::WithShot,
                                            it->position);
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

void PhysicEngine::handleEntitiesCollisions() {
    Vec2f collisionPoint;

    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            const auto entityPoly1 = entities[i];
            const auto entityPoly2 = entities[j];

            if (*entityPoly1.first != *entityPoly2.first) {
                if (isCirclesCollides(entityPoly1.first->getPosition(),
                                      entityPoly1.second,
                                      entityPoly2.first->getPosition(),
                                      entityPoly2.second,
                                      &collisionPoint)) {

                    entityPoly1.first->onCollide(
                            CollisionType::WithAsteroid,
                            collisionPoint
                    );
                    entityPoly2.first->onCollide(
                            CollisionType::WithAsteroid,
                            collisionPoint
                    );

                }
            }
        }
    }
}

void PhysicEngine::handlePlayerCollisions() {
    for (const auto& entityPoly : entities) {
        if (isPlayerCollides(player,
                             entityPoly.first->getPosition(),
                             entityPoly.second)) {
            player->onCollide();
        }
    }
}

bool PhysicEngine::isPointInCircle(const Vec2f& point,
                                   const Vec2f& center,
                                   const Circle& circle) {
    return (center - point).sqrLength() < circle.getSqrRadius();
}

bool PhysicEngine::isCirclesCollides(const Vec2f& pos1, const Circle& circle1,
                                     const Vec2f& pos2, const Circle& circle2,
                                     Vec2f* collisionPoint) {

    const auto v = pos2 - pos1;
    if (v.length() <= circle1.getRadius() + circle2.getRadius()) {
        if (collisionPoint) {
            const auto d = v.length();
            const auto a = (circle1.getSqrRadius()
                            - circle2.getSqrRadius() + d * d) / (2.f * d);
            *collisionPoint = pos1 + v.normalized() * a;
        }
        return true;
    }
    return false;
}

bool PhysicEngine::isPlayerCollides(const std::shared_ptr<Player> &player,
                                    const Vec2f &center,
                                    const Circle &circle) {
    return isPointInCircle(player->getAbsoluteCollidePoint(0), center, circle)
        || isPointInCircle(player->getAbsoluteCollidePoint(1), center, circle)
        || isPointInCircle(player->getAbsoluteCollidePoint(2), center, circle);
}
