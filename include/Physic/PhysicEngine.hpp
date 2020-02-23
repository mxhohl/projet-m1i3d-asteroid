#ifndef PROJETPROGAVANCEE_PHYSICENGINE_HPP
#define PROJETPROGAVANCEE_PHYSICENGINE_HPP

#include "Rendering/Polygon.hpp"
#include "Observer/Observer.hpp"
#include "Entities/Shot.hpp"

#include <memory>

class PhysicEntity;

class PhysicEngine : public Updatable, public Renderable {
public:
    enum class CollisionType {
        WithShot,
        WithAsteroid
    };

public:
    PhysicEngine();

    void update(double& dt) override;
    void update(Renderer& rend) override;

    void addEntity(const std::shared_ptr<PhysicEntity>& entity,
                   const Polygon& shape);
    void setShots(const std::shared_ptr<std::vector<Shot>>& sht);

private:
    void handleShotsCollisions();

private:
    [[nodiscard]] Polygon generateConvexHull(const Polygon& baseShape) const;
    static bool isPointInPolygon(const Vec2f& point,
                                 const Polygon& polygon);

private:
    std::vector<std::pair<std::shared_ptr<PhysicEntity>, Polygon>> entities;
    std::shared_ptr<std::vector<Shot>> shots;

};

#endif //PROJETPROGAVANCEE_PHYSICENGINE_HPP
