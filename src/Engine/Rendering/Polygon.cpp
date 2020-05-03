#include "Engine/Rendering/Polygon.hpp"

#include <utility>
#include <algorithm>

using namespace engine;

Polygon::Polygon() = default;

Polygon::Polygon(size_t size) : points(size) {}

Polygon::Polygon(std::initializer_list<Vec2f> points) {
    for (auto point : points) {
        addPoint(point);
    }
}

Polygon::Polygon(const std::vector<Vec2f>& points) {
    for (auto point : points) {
        addPoint(point);
    }
}

void Polygon::addPoint(Vec2f point) {
    if (!std::any_of(points.begin(), points.end(), [point](const Vec2f& c){
        return c == point;
    })) {
        points.push_back(point);
    }
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

const std::vector<Vec2f>& Polygon::getPoints() const {
    return points;
}

Vec2f Polygon::getCentroid() const {
    float signedArea = 0;
    float x = 0;
    float y = 0;

    size_t i;
    for (i = 0; i < points.size() -1; ++i) {
        const float a = points[i].x() * points[i + 1].y()
                        - points[i + 1].x() * points[i].y();

        signedArea += a;
        x += (points[i].x() + points[i + 1].x()) * a;
        y += (points[i].y() + points[i + 1].y()) * a;
    }

    const float a = points[i].x() * points[0].y()
                    - points[0].x() * points[i].y();

    signedArea += a;
    x += (points[i].x() + points[0].x()) * a;
    y += (points[i].y() + points[0].y()) * a;

    signedArea = 1.f / (6.f * signedArea);
    x *= signedArea;
    y *= signedArea;

    return Vec2f(x, y);
}

void Polygon::reorderPoints() {
    const Vec2f centroid = getCentroid();
    std::sort(points.begin(), points.end(), [centroid](const Vec2f& a,
                                                       const Vec2f& b){
        Vec2f ray1 = a - centroid;
        Vec2f ray2 = b - centroid;
        return std::atan2(ray1.x(), ray1.y()) < std::atan2(ray2.x(), ray2.y());
    });
}
