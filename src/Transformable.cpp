#include "Transformable.hpp"

#include <cmath>

Transformable::Transformable() : position{0, 0}, rotation(0), scale{1, 1} {

}

const Vec2f& Transformable::getPosition() const {
    return position;
}

void Transformable::setPosition(const Vec2f& pos) {
    position = pos;
}

void Transformable::move(const Vec2f &offset) {
    position += offset;
}

float Transformable::getRotation() const {
    return rotation;
}

void Transformable::setRotation(float rot) {
    rotation = rot;
}

void Transformable::setRotationDeg(float rot) {
    rotation = rot * DEG_TO_RAD;
}

void Transformable::rotate(float rot) {
    rotation += rot;
}

void Transformable::rotateDeg(float rot) {
    rotation += rot * DEG_TO_RAD;
}

const Vec2f& Transformable::getScale() const {
    return scale;
}

void Transformable::setScale(const Vec2f& s) {
    scale = s;
}

void Transformable::setScale(float s) {
    scale = {s, s};
}

Mat3f Transformable::getTransformMatrix() const {
    return Mat3f::rotation(rotation)
         * Mat3f::scale(scale)
         * Mat3f::translation(position);
}
