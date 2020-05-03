#include "Engine/gui/Entities/Panel.hpp"

#include <utility>

using namespace engine::gui;

Panel::Panel(std::shared_ptr<Gui> gui) :
        Entity(std::move(gui)),
        width(100), height(100) {}

Panel::~Panel() = default;

unsigned int Panel::getWidth() const {
    return width;
}

void Panel::setWidth(int w) {
    width = w;
}

unsigned int Panel::getHeight() const {
    return height;
}

void Panel::setHeight(int h) {
    height = h;
}

const engine::Color &Panel::getColor() const {
    return color;
}

void Panel::setColor(const Color &c) {
    color = c;
}

void Panel::onRender(GUIRenderer &renderer) const {
    renderer.setDrawColor(color);
    renderer.draw(RectI({0, 0}, {width, height}));
}
