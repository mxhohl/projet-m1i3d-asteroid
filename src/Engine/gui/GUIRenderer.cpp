#include "Engine/gui/GUIRenderer.hpp"

#include <utility>

using namespace gui;

GUIRenderer::GUIRenderer(Renderer& renderer,
                         Vec2i currentDPos) :
        renderer(renderer),
        currentDPos(std::move(currentDPos)) {}

GUIRenderer::GUIRenderer(const GUIRenderer& parent, Vec2i position) :
        renderer(parent.renderer),
        currentDPos(parent.currentDPos + position) {}

void GUIRenderer::setDrawColor(const Color& color) {
    renderer.setDrawColor(color);
}

Color GUIRenderer::getDrawColor() const {
    return renderer.getDrawColor();
}

void GUIRenderer::draw(const Vec2i &start, const Vec2i &end) {
    renderer.draw(Vec2f(currentDPos + start), Vec2f(currentDPos + end));
}

void GUIRenderer::draw(const RectI &rect) {
    renderer.draw(RectF(
            currentDPos.x() + rect.x(),
            currentDPos.y() + rect.y(),
            rect.width(),
            rect.height()
    ), true);
}
