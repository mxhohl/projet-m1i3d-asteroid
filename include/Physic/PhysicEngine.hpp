#ifndef PROJETPROGAVANCEE_PHYSICENGINE_HPP
#define PROJETPROGAVANCEE_PHYSICENGINE_HPP

#include "Types/Circle.hpp"
#include "Observer/Observer.hpp"
#include "Entities/Shot.hpp"

#include <memory>

class PhysicEntity;
class Player;

class PhysicEngine : public Updatable {
public:
    enum class CollisionType {
        WithShot,
        WithAsteroid
    };

public:
    PhysicEngine();

    void update(double dt) override;

    void addEntity(const std::shared_ptr<PhysicEntity>& entity,
                   const Circle& bb);
    void removeEntity(const std::shared_ptr<PhysicEntity>& entity);

    void setShots(const std::shared_ptr<std::vector<Shot>>& sht);

    void setPlayer(const std::shared_ptr<Player>& p);

    void reset();

private:
    void handleShotsCollisions();
    void handleEntitiesCollisions();
    void handlePlayerCollisions();

private:
    static bool isPointInCircle(const Vec2f& point,
                                const Vec2f& center,
                                const Circle& circle);
    static bool isCirclesCollides(const Vec2f& pos1, const Circle& circle1,
                                  const Vec2f& pos2, const Circle& circle2,
                                  Vec2f* collisionPoint);
    static bool isPlayerCollides(const std::shared_ptr<Player>& player,
                                 const Vec2f& center,
                                 const Circle& circle);

private:
    std::vector<std::pair<std::shared_ptr<PhysicEntity>, Circle>> entities;
    std::shared_ptr<std::vector<Shot>> shots;
    std::shared_ptr<Player> player;
    uint32_t entityUidCounter;
};

#endif //PROJETPROGAVANCEE_PHYSICENGINE_HPP
