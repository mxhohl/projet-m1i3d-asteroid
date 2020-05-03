#ifndef PROJETPROGAVANCEE_POLYGON_HPP
#define PROJETPROGAVANCEE_POLYGON_HPP

#include "Engine/Types/Vec2.hpp"

#include <vector>

namespace engine {

class Polygon {
public:
    Polygon();
    explicit Polygon(size_t size);
    Polygon(std::initializer_list<Vec2f> points);
    explicit Polygon(const std::vector<Vec2f> &points);

    void addPoint(Vec2f point);
    void removePoint(size_t i);

    [[nodiscard]] size_t pointsCount() const;

    Vec2f &operator[](size_t i);
    const Vec2f &operator[](size_t i) const;

    [[nodiscard]] const std::vector<Vec2f> &getPoints() const;

    [[nodiscard]] Vec2f getCentroid() const;

    void reorderPoints();

private:
    std::vector<Vec2f> points;
};

}

#endif //PROJETPROGAVANCEE_POLYGON_HPP
