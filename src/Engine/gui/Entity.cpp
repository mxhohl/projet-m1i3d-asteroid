#include "Engine/gui/Entity.hpp"
#include "Engine/gui/Gui.hpp"
#include "Engine/Settings.hpp"

#include <algorithm>
#include <utility>

using namespace engine::gui;

Entity::Entity(std::shared_ptr<Gui>  gui) :
        gui(std::move(gui)),
        parent(),
        position(0, 0), anchor(Anchor::TopLeft), visible(true) {}

Entity::~Entity() {
    removeInParent();
}

std::shared_ptr<Entity> Entity::getParent() const {
    return parent.expired() ? nullptr : std::shared_ptr(parent);
}

void Entity::setParent(const std::shared_ptr<Entity>& newParent) {
    removeInParent();
    setNewParent(newParent);
}

engine::Vec2u Entity::getSize() const {
    return {getWidth(), getHeight()};
}

const engine::Vec2i& Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vec2i& pos) {
    position = pos;
}

void Entity::move(const Vec2i& dp) {
    position += dp;
}

engine::Vec2i Entity::getRelativePosition() const {
    auto parentAbsolutePos = Vec2i(0, 0);

    if (!parent.expired()) {
        const auto parent_ptr = std::shared_ptr(parent);

        switch (anchor) {
            case Anchor::TopLeft:
                break;
            case Anchor::TopMiddle:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() / 2 - getWidth() / 2,
                        0
                );
                break;
            case Anchor::TopRight:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() - getWidth(),
                        0
                );
                break;
            case Anchor::MiddleLeft:
                parentAbsolutePos += Vec2i(
                        0,
                        parent_ptr->getHeight() / 2 - getHeight() / 2
                );
                break;
            case Anchor::Middle:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() / 2 - getWidth() / 2,
                        parent_ptr->getHeight() / 2 - getHeight() / 2
                );
                break;
            case Anchor::MiddleRight:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() - getWidth(),
                        parent_ptr->getHeight() / 2 - getHeight() / 2
                );
                break;
            case Anchor::BottomLeft:
                parentAbsolutePos += Vec2i(
                        0,
                        parent_ptr->getHeight() - getHeight()
                );
                break;
            case Anchor::BottomMiddle:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() / 2 - getWidth() / 2,
                        parent_ptr->getHeight() - getHeight()
                );
                break;
            case Anchor::BottomRight:
                parentAbsolutePos += Vec2i(
                        parent_ptr->getWidth() - getWidth(),
                        parent_ptr->getHeight() - getHeight()
                );
                break;
        }
    } else {
        const auto& settings = Settings::getInstance();
        const auto width = settings.getParameter<int>("window_width");
        const auto height = settings.getParameter<int>("window_height");

        switch (anchor) {
            case Anchor::TopLeft:
                break;
            case Anchor::TopMiddle:
                parentAbsolutePos += Vec2i(
                        width / 2 - getWidth() / 2,
                        0
                );
                break;
            case Anchor::TopRight:
                parentAbsolutePos += Vec2i(
                        width - getWidth(),
                        0
                );
                break;
            case Anchor::MiddleLeft:
                parentAbsolutePos += Vec2i(
                        0,
                        height / 2 - getHeight() / 2
                );
                break;
            case Anchor::Middle:
                parentAbsolutePos += Vec2i(
                        width / 2 - getWidth() / 2,
                        height / 2 - getHeight() / 2
                );
                break;
            case Anchor::MiddleRight:
                parentAbsolutePos += Vec2i(
                        width - getWidth(),
                        height / 2 - getHeight() / 2
                );
                break;
            case Anchor::BottomLeft:
                parentAbsolutePos += Vec2i(
                        0,
                        height - getHeight()
                );
                break;
            case Anchor::BottomMiddle:
                parentAbsolutePos += Vec2i(
                        width / 2 - getWidth() / 2,
                        height - getHeight()
                );
                break;
            case Anchor::BottomRight:
                parentAbsolutePos += Vec2i(
                        width - getWidth(),
                        height - getHeight()
                );
                break;
        }
    }

    return parentAbsolutePos + position;
}

engine::Vec2i Entity::getAbsolutePosition() const {
    if (parent.expired()) {
        return getRelativePosition();
    } else {
        const auto parent_ptr = std::shared_ptr(parent);
        return getRelativePosition() + parent_ptr->getAbsolutePosition();
    }
}

Anchor Entity::getAnchor() const {
    return anchor;
}

void Entity::setAnchor(Anchor a) {
    anchor = a;
}


void Entity::show() {
    visible = true;
    onShow();
}

void Entity::hide() {
    visible = false;
    onHide();
}

void Entity::setVisible(bool v) {
    bool changed = v != visible;
    visible = v;

    if (changed) {
        if (visible) {
            onShow();
        } else {
            onHide();
        }
    }
}

bool Entity::isVisible() const {
    return visible;
}

void Entity::toggleVisibility() {
    setVisible(!visible);
}

void Entity::onHide() {
    std::for_each(begin(), end(), [](auto& elem) {
        elem->hide();
    });
}

void Entity::onShow() {
    std::for_each(begin(), end(), [](auto& elem) {
        elem->show();
    });
}

void Entity::render(GUIRenderer& parentRenderer) const {
    if (!visible) {
        return;
    }

    GUIRenderer renderer(parentRenderer, getRelativePosition());

    onRender(renderer);

    for (const auto& entity : children) {
        entity->render(renderer);
    }
}

void Entity::setNewParent(const std::shared_ptr<Entity>& toSet) {
    parent = toSet;
    if (toSet) {
        toSet->children.push_back(shared_from_this());
    } else {
        gui->children.push_back(shared_from_this());
    }
}

void Entity::removeInParent() {
    if (!parent.expired()) {
        auto parent_ptr = std::shared_ptr(parent);
        auto it = std::find(
                parent_ptr->children.begin(),
                parent_ptr->children.end(),
                shared_from_this()
        );
        if (it != parent_ptr->children.end()) {
            parent_ptr->children.erase(it);
        }
    } else {
        auto it = std::find(
                gui->children.begin(),
                gui->children.end(),
                shared_from_this()
        );
        if (it != gui->children.end()) {
            gui->children.erase(it);
        }
    }
}
