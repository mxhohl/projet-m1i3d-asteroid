#include "gui/Text.hpp"

#include <utility>
#include <iostream>

using namespace gui;

Text::Text(uint32_t uid) : Entity(uid) {}

Text::~Text() = default;

const std::string& Text::getText() const {
    return text;
}

void Text::setText(const std::string& t) {
    text = t;
}

const Color& Text::getColor() const {
    return color;
}

void Text::setColor(const Color& col) {
    color = col;
}

float Text::getHeight() const {
    return static_cast<float>(BASE_HEIGHT) * getScale().y();
}

float Text::getWidth() const {
    return getWidth(text);
}

float Text::getWidth(const std::string &str) {
    return getWidth(str.c_str());
}

float Text::getWidth(const char* str) {
    if (*str == '\0') {
        return 0;
    }

    float charWidth = 0;

    if (*str < 32 || *str > 126) {
        charWidth = getWidth("?");
    } else {
        charWidth = static_cast<float>(CHARS[*str - ' '][1]);
    }

    return charWidth + getWidth(++str);
}

void Text::render(Renderer& renderer) {
    const auto transform = getTransformMatrix();
    const auto lineHeightVec = Vec2f(0, getHeight());

    int currentPos = 0;
    renderer.setDrawColor(color);
    for (const auto c : text) {
        currentPos = renderChar(renderer, c, currentPos,
                                lineHeightVec, transform);
    }
}

int Text::renderChar(Renderer& renderer, char c, int& spacing,
                     const Vec2f& lineHeightVec, const Mat3f& transform) {
    if (c < 32 || c > 126) {
        return renderChar(renderer, '?', spacing, lineHeightVec, transform);
    }

    Vec2f spacingVec(spacing, 0);

    const int* currentChar = CHARS[c - ' '];
    const int size = currentChar[0];
    const int charWidth = currentChar[1];

    static const auto mirrorMat = Mat3f::scale({1, -1});

    auto prevPoint = mirrorMat.transformPoint(Vec2f(
            currentChar[2],
            currentChar[3]
    ));
    bool skipping = false;

    for (int i = 4; i < size * 2 + 1; i += 2) {
        Vec2f rawPoint = Vec2f(
                currentChar[i],
                currentChar[i + 1]
        );

        if (rawPoint == Vec2f{-1,-1}) {
            skipping = true;
        } else {
            Vec2f point = mirrorMat.transformPoint(rawPoint);

            if (!skipping && point != Vec2f{-1, -1}) {
                renderer.draw(
                        prevPoint + spacingVec + lineHeightVec,
                        point + spacingVec + lineHeightVec,
                        transform
                );
            } else if (skipping) {
                skipping = false;
            }

            prevPoint = point;
        }
    }

    spacing += charWidth;
    return spacing;
}
