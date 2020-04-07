#include "gui/Panel.hpp"

#include <algorithm>
#include <iostream>

using namespace gui;

Panel::Panel(uint32_t uid) : Entity(uid), width(100), height(100) {}

Panel::~Panel() = default;

void Panel::addEntity(const std::shared_ptr<Entity>& entity, Anchor anchor) {
    auto res = std::find_if(
            elements.begin(),
            elements.end(),
            [entity](auto& elem) {
        return elem.second == entity;
    });

    if (res != elements.end()) {
        std::cerr << "The element is already in the panel" << std::endl;
        return;
    }

    elements.emplace_back(anchor, entity);
}

float Panel::getWidth() const {
    return width;
}

void Panel::setWidth(float w) {
    width = w;
}

float Panel::getHeight() const {
    return height;
}

void Panel::setHeight(float h) {
    height = h;
}

const Color &Panel::getColor() const {
    return color;
}

void Panel::setColor(const Color &c) {
    color = c;
}

void Panel::render(Renderer &renderer) {
    renderer.setDrawColor(color);
    renderer.draw(
        Rect(Vec2f{0, 0}, {width, height}),
        true,
        getTransformMatrix()
    );
}

void Panel::onHide() {
    std::for_each(elements.begin(), elements.end(), [](auto& elem) {
        elem.second->hide();
    });
}

void Panel::onShow() {
    std::for_each(elements.begin(), elements.end(), [](auto& elem) {
        elem.second->show();
    });
}
