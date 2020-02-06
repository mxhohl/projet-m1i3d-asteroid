#include "Rendering/Polygon.hpp"


Polygon::Polygon() : scale(1.) {}

Polygon::Polygon(size_t size) : points(size), scale(1.) {}

Polygon::Polygon(std::initializer_list<Vec2f> points) : scale(1.) {
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

Vec2f Polygon::getPointInWorldPos(size_t i) const {
    return points[i] * scale + position;
}

float Polygon::getScale() const {
    return scale;
}

void Polygon::setScale(float newScale) {
    scale = newScale;
}

const Vec2f& Polygon::getPosition() const {
    return position;
}

void Polygon::setPosition(const Vec2f& pos) {
    position = pos;
}
