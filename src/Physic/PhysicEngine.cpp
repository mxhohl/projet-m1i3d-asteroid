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

void PhysicEngine::update(Renderer& rend) {
#ifdef DEBUG
    rend.setDrawColor({0, 255, 255, 255});
    for (auto& entityPoly : entities) {
        rend.draw(entityPoly.second, entityPoly.first->getTransformMatrix());
    }
#else
    (void)rend;
#endif
}

void PhysicEngine::addEntity(const std::shared_ptr<PhysicEntity>& entity,
                             const Polygon& shape) {
    entities.emplace_back(entity, generateConvexHull(shape));
}

void PhysicEngine::setShots(const std::shared_ptr<std::vector<Shot>>& sht) {
    shots = sht;
}

void PhysicEngine::handleShotsCollisions() {
    for (auto it = shots->begin(); it != shots->end(); ++it) {
        for (auto& entityPoly : entities) {
            if (isPointInPolygon(it->position, entityPoly.second)) {
                entityPoly.first->onCollide(CollisionType::WithShot);
                shots->erase(it);
            }
        }
    }
}

float sidedDist(Vec2f a, Vec2f b, Vec2f p) {
    return (p.y() - a.y()) * (b.x() - a.x())
         - (b.y() - a.y()) * (p.x() - a.x());
}

template <class T>
inline int getSign(T val) {
    if (val < 0) {
        return -1;
    } else if (val > 0) {
        return 1;
    }
    return 0;
}

void quickHull(const std::vector<Vec2f>& points,
               const Vec2f& a, const Vec2f& b,
               int side,
               std::vector<Vec2f>& result) {
    int maxDistInd = -1;
    float maxDist = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        const float dist = sidedDist(a, b, points[i]);
        if (getSign(dist) == side && std::abs(dist) > maxDist) {
            maxDistInd = i;
            maxDist = std::abs(dist);
        }
    }

    if (maxDistInd == -1) {
        result.push_back(a);
        result.push_back(b);
        return;
    }

    quickHull(points,
              points[maxDistInd],
              a,
              -getSign(sidedDist(points[maxDistInd], a, b)),
              result);
    quickHull(points,
              points[maxDistInd],
              b,
              -getSign(sidedDist(points[maxDistInd], b, a)),
              result);
}

/* Use the Quickhull algorithm */
Polygon PhysicEngine::generateConvexHull(const Polygon& baseShape) const {
    if (baseShape.pointsCount() < 4) {
        return baseShape;
    }

    size_t minInd = 0;
    size_t maxInd = 1;
    for (size_t i = 2; i < baseShape.pointsCount(); ++i) {
        if (baseShape[minInd].x() > baseShape[i].x()) {
            minInd = i;
        }
        if (baseShape[maxInd].x() < baseShape[i].x()) {
            maxInd = i;
        }
    }

    const std::vector<Vec2f>& points = baseShape.getPoints();

    std::vector<Vec2f> convexHullPoints;
    quickHull(points,
              baseShape[minInd], baseShape[maxInd],
              1,
              convexHullPoints);
    quickHull(points,
              baseShape[minInd], baseShape[maxInd],
              -1,
              convexHullPoints);

    Polygon convexHull(convexHullPoints);
    convexHull.reorderPoints();
    return convexHull;
}

bool PhysicEngine::isPointInPolygon(const Vec2f& point,
                                    const Polygon& polygon) {
    bool result = false;
    for (size_t i = 0, j = polygon.pointsCount() -1;
         i < polygon.pointsCount();
         j = i++) {
        if ((polygon[i].y() > point.y()) != (polygon[j].y() > point.y()) &&
            (point.x() < (polygon[j].x() - polygon[i].x())
                * (point.y() - polygon[i].y())
                / (polygon[j].y() - polygon[i].y())
                + polygon[i].x())) {
            result = !result;
        }
    }
    return result;
}
