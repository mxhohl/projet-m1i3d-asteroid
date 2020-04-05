#ifndef PROJETPROGAVANCEE_ENTITY_HPP
#define PROJETPROGAVANCEE_ENTITY_HPP

#include <cstdint>
#include "Transformable.hpp"
#include "Rendering/Renderer.hpp"

namespace gui {

class Entity : public Transformable {
    friend class Gui;

protected:
    explicit Entity(uint32_t uid) : uid(uid) {}

public:
    virtual ~Entity() = default;

    friend bool operator==(const Entity& left, const Entity& right) {
        return left.uid == right.uid && left.uid != 0;
    }

    [[nodiscard]] virtual float getWidth() const = 0;
    [[nodiscard]] virtual float getHeight() const = 0;

protected:
    virtual void render(Renderer& renderer) = 0;

private:
    uint32_t uid = 0;

};

}

#endif //PROJETPROGAVANCEE_ENTITY_HPP
