#ifndef PROJETPROGAVANCEE_ENTITY_HPP
#define PROJETPROGAVANCEE_ENTITY_HPP

#include "Anchor.hpp"
#include "Engine/Types/Vec2.hpp"
#include "Engine/Rendering/Renderer.hpp"
#include "GUIRenderer.hpp"

#include <memory>
#include <vector>

namespace gui {

class Gui;

class Entity : public std::enable_shared_from_this<Entity> {
    friend class Gui;

protected:
    explicit Entity(std::shared_ptr<Gui> gui);

public:
    virtual ~Entity();

    [[nodiscard]] std::shared_ptr<Entity> getParent() const;
    void setParent(const std::shared_ptr<Entity>& newParent);

    [[nodiscard]] virtual unsigned int getWidth() const = 0;
    [[nodiscard]] virtual unsigned int getHeight() const = 0;
    [[nodiscard]] Vec2u getSize() const;

    [[nodiscard]] const Vec2i& getPosition() const;
    void setPosition(const Vec2i& pos);
    void move(const Vec2i& dp);

    [[nodiscard]] Vec2i getRelativePosition() const;
    [[nodiscard]] Vec2i getAbsolutePosition() const;

    [[nodiscard]] Anchor getAnchor() const;
    void setAnchor(Anchor a);

    void show();
    void hide();
    void setVisible(bool v);
    [[nodiscard]] bool isVisible() const;
    void toggleVisibility();

public:
    std::vector<std::shared_ptr<Entity>>::iterator begin() noexcept {
        return children.begin();
    }

    std::vector<std::shared_ptr<Entity>>::const_iterator begin() const noexcept {
        return children.begin();
    }

    std::vector<std::shared_ptr<Entity>>::iterator end() {
        return children.end();
    }

    std::vector<std::shared_ptr<Entity>>::const_iterator end() const noexcept {
        return children.end();
    }

protected:
    virtual void onRender(GUIRenderer& renderer) const = 0;
    virtual void onHide();
    virtual void onShow();

private:
    void render(GUIRenderer& parentRenderer) const;
    void setNewParent(const std::shared_ptr<Entity>& toSet);
    void removeInParent();

private:
    std::shared_ptr<Gui> gui;
    std::weak_ptr<Entity> parent;
    std::vector<std::shared_ptr<Entity>> children;

    Vec2i position;
    Anchor anchor;
    bool visible;

};

}

#endif //PROJETPROGAVANCEE_ENTITY_HPP
