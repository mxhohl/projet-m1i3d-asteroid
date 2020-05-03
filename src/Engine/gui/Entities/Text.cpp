#include "Engine/gui/Entities/Text.hpp"

#include <iostream>

using namespace engine::gui;

Text::Text(std::shared_ptr<Gui> gui) :
        Entity(std::move(gui)),
        text(""),
        characterSize(BASE_HEIGHT),
        scale(static_cast<float>(characterSize) / BASE_HEIGHT),
        color(0, 0, 0, 255) {}

Text::~Text() = default;

const std::string& Text::getText() const {
    return text;
}

void Text::setText(const std::string& t) {
    text = t;
}

const engine::Color& Text::getColor() const {
    return color;
}

void Text::setColor(const Color& col) {
    color = col;
}

unsigned int Text::getCharacterSize() const {
    return characterSize;
}

void Text::setCharacterSize(unsigned int size) {
    characterSize = size;
    scale = static_cast<float>(characterSize) / BASE_HEIGHT;
}

unsigned int Text::getHeight() const {
    return characterSize;
}

unsigned int Text::getWidth() const {
    return getWidth(text.c_str());
}

unsigned int Text::getWidth(const char* str) const {
    if (*str == '\0') {
        return 0;
    }

    unsigned int charWidth;

    if (*str < 32 || *str > 126) {
        charWidth = getWidth("?");
    } else {
        charWidth = static_cast<int>(
                static_cast<float>(CHARS[*str - ' '][1]) * scale
        );
    }

    return charWidth + getWidth(++str);
}

void Text::onRender(GUIRenderer& renderer) const {
    const auto lineHeightVec = Vec2i(0, getHeight());

    int currentPos = 0;
    renderer.setDrawColor(color);

    for (const auto c : text) {
        currentPos = renderChar(renderer, c, currentPos, lineHeightVec);
    }
}

int Text::renderChar(GUIRenderer& renderer, char c, int spacing,
                     const Vec2i& lineHeightVec) const {
    if (c < 32 || c > 126) {
        return renderChar(renderer, '?', spacing, lineHeightVec);
    }

    Vec2i spacingVec(spacing, 0);

    const int* currentChar = CHARS[c - ' '];
    const int size = currentChar[0];
    const int charWidth = static_cast<int>(
            static_cast<float>(currentChar[1]) * scale
    );

    const auto mirrorMat = Mat3f::scale({scale, -scale});

    auto prevPoint = Vec2i(mirrorMat.transformPoint(Vec2f(
            currentChar[2],
            currentChar[3]
    )));
    bool skipping = false;

    for (int i = 4; i < size * 2 + 1; i += 2) {
        Vec2f rawPoint = Vec2f(
                currentChar[i],
                currentChar[i + 1]
        );

        if (rawPoint == Vec2f{-1,-1}) {
            skipping = true;
        } else {
            Vec2i point(mirrorMat.transformPoint(rawPoint));

            if (!skipping && point != Vec2i{-1, -1}) {
                renderer.draw(
                        prevPoint + spacingVec + lineHeightVec,
                        point + spacingVec + lineHeightVec
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
