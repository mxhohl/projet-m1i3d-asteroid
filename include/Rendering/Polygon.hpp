#ifndef PROJETPROGAVANCEE_POLYGON_HPP
#define PROJETPROGAVANCEE_POLYGON_HPP

#include "Types/Vec2.hpp"

#include <vector>

class Polygon {
public:
    Polygon();
    explicit Polygon(size_t size);
    Polygon(std::initializer_list<Vec2f> points);

    void addPoint(Vec2f point);
    void removePoint(size_t i);

    [[nodiscard]] size_t pointsCount() const;

    Vec2f& operator[](size_t i);
    const Vec2f& operator[](size_t i) const;

private:
    std::vector<Vec2f> points;
};

#endif //PROJETPROGAVANCEE_POLYGON_HPP
