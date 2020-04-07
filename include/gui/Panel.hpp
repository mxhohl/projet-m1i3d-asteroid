#ifndef PROJETPROGAVANCEE_PANEL_HPP
#define PROJETPROGAVANCEE_PANEL_HPP

#include "Entity.hpp"
#include "Anchor.hpp"

#include <vector>
#include <memory>

namespace gui {

class Panel : public Entity {
public:
    using Ptr = std::shared_ptr<Panel>;

public:
    explicit Panel(uint32_t uid);
    ~Panel() override;

    [[nodiscard]] float getWidth() const override;
    void setWidth(float w);

    [[nodiscard]] float getHeight() const override;
    void setHeight(float h);

    [[nodiscard]] const Color& getColor() const;
    void setColor(const Color& c);

public:
    void addEntity(const std::shared_ptr<Entity>& entity,
                   Anchor anchor = Anchor::TopLeft);

protected:
    void render(Renderer& renderer) override;
    void onHide() override;
    void onShow() override;

private:
    float width;
    float height;
    Color color;

    std::vector<std::pair<Anchor, std::shared_ptr<Entity>>> elements;
};

}

#endif //PROJETPROGAVANCEE_PANEL_HPP
