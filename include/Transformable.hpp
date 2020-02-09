#ifndef PROJETPROGAVANCEE_TRANSFORMABLE_HPP
#define PROJETPROGAVANCEE_TRANSFORMABLE_HPP

#include "Types/Mat3.hpp"
#include "Types/Vec2.hpp"

#include <SDL_types.h>

class Transformable {
private:
    static constexpr float DEG_TO_RAD = M_PI / 180.f;

public:
    Transformable();

    [[nodiscard]] const Vec2f& getPosition() const;
    void setPosition(const Vec2f& pos);
    void move(const Vec2f& offset);

    [[nodiscard]] float getRotation() const;
    void setRotation(float rot);
    void setRotationDeg(float rot);
    void rotate(float rot);
    void rotateDeg(float rot);

    [[nodiscard]] const Vec2f& getScale() const;
    void setScale(const Vec2f& s);
    void setScale(float s);

    [[nodiscard]] Mat3f getTransformMatrix() const;

private:
    Vec2f position;
    float rotation;
    Vec2f scale;

};

#endif //PROJETPROGAVANCEE_TRANSFORMABLE_HPP
