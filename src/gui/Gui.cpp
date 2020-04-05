#include "gui/Gui.hpp"

using namespace gui;

Gui::Gui() : uidCount(1) {

}

Gui::~Gui() = default;

void Gui::update(Renderer& renderer) {
    for (const auto& entity : entities) {
        entity.second->render(renderer);
    }
}
