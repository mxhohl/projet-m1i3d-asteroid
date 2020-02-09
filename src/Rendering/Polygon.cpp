#include "Rendering/Polygon.hpp"


Polygon::Polygon() = default;

Polygon::Polygon(size_t size) : points(size) {}

Polygon::Polygon(std::initializer_list<Vec2f> points) {
    for (auto point : points) {
        this->points.push_back(point);
    }
}

void Polygon::addPoint(Vec2f point) {
    points.push_back(point);
}

void Polygon::removePoint(size_t i) {
    points.erase(points.begin() + i);
}

size_t Polygon::pointsCount() const {
    return points.size();
}

Vec2f& Polygon::operator[](size_t i) {
    return points[i];
}

const Vec2f& Polygon::operator[](size_t i) const {
    return points[i];
}
