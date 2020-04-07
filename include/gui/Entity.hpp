#ifndef PROJETPROGAVANCEE_ENTITY_HPP
#define PROJETPROGAVANCEE_ENTITY_HPP

#include <cstdint>
#include "Transformable.hpp"
#include "Rendering/Renderer.hpp"

namespace gui {

class Entity : public Transformable {
    friend class Gui;

protected:
    explicit Entity(uint32_t uid) : uid(uid), visible(true) {}

public:
    virtual ~Entity() = default;

    friend bool operator==(const Entity& left, const Entity& right) {
        return left.uid == right.uid && left.uid != 0;
    }

    [[nodiscard]] virtual float getWidth() const = 0;
    [[nodiscard]] virtual float getHeight() const = 0;

    void show() {
        visible = true;
        onShow();
    }

    void hide() {
        visible = false;
        onHide();
    }

    void setVisible(bool v) {
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

    [[nodiscard]] bool isVisible() const {
        return visible;
    }

    void toggleVisibility() {
        setVisible(!visible);
    }

protected:
    virtual void render(Renderer& renderer) = 0;
    virtual void onHide() {}
    virtual void onShow() {}

private:
    uint32_t uid = 0;
    bool visible;

};

}

#endif //PROJETPROGAVANCEE_ENTITY_HPP
