#ifndef PROJETPROGAVANCEE_CIRCLE_HPP
#define PROJETPROGAVANCEE_CIRCLE_HPP

#include "Engine/Rendering/Polygon.hpp"
#include "Mat3.hpp"
#include "Engine/Utils.hpp"

#include <optional>
#include <string>

namespace engine {

class Circle {
public:
    explicit Circle(float radius) : radius(radius) {}

    friend std::ostream &operator<<(std::ostream &s, const Circle &circle) {
        s << std::string("Circle(")
          << std::to_string(circle.radius)
          << std::string(")");
        return s;
    }

    void setRadius(float r) {
        radius = r;
    }

    float getRadius() const {
        return radius;
    }

    float getSqrRadius() const {
        return radius * radius;
    }

    const Polygon &getPolygon(size_t ptCount = 20) const {
        if (!polygon) {
            generatePolygon(ptCount);
        }
        return polygon.value();
    }

private:
    void generatePolygon(size_t count) const {
        Polygon poly;
        Vec2f vec = {radius, 0, 0};
        auto rotation = Mat3f::rotation(M_PI * 2.0 / float(count));

        for (size_t i = 0; i < count; ++i) {
            poly.addPoint(vec);
            vec = rotation.transformPoint(vec);
        }

        polygon = poly;
    }

private:
    float radius;

    mutable std::optional<Polygon> polygon;
};

}

#endif //PROJETPROGAVANCEE_CIRCLE_HPP