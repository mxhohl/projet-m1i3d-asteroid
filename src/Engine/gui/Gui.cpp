#include "Engine/gui/Gui.hpp"

using namespace engine::gui;

Gui::Gui() = default;

Gui::~Gui() = default;

void Gui::update(Renderer& renderer) {
    GUIRenderer guiRenderer(renderer, {0, 0});

    for (const auto& entity : children) {
        entity->render(guiRenderer);
    }
}
