#ifndef PROJETPROGAVANCEE_PHYSICENGINE_HPP
#define PROJETPROGAVANCEE_PHYSICENGINE_HPP

#include "Types/Circle.hpp"
#include "Observer/Observer.hpp"
#include "Entities/Shot.hpp"

#include <memory>

class PhysicEntity;

class PhysicEngine : public Updatable {
public:
    enum class CollisionType {
        WithShot,
        WithAsteroid
    };

public:
    PhysicEngine();

    void update(double& dt) override;

    void addEntity(const std::shared_ptr<PhysicEntity>& entity,
                   const Circle& bb);
    void setShots(const std::shared_ptr<std::vector<Shot>>& sht);

private:
    void handleShotsCollisions();

private:
    static bool isPointInCircle(const Vec2f& point,
                                const Vec2f& center,
                                const Circle& circle);

private:
    std::vector<std::pair<std::shared_ptr<PhysicEntity>, Circle>> entities;
    std::shared_ptr<std::vector<Shot>> shots;

};

#endif //PROJETPROGAVANCEE_PHYSICENGINE_HPP
