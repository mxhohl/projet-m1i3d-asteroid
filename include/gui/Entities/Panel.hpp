#ifndef PROJETPROGAVANCEE_PANEL_HPP
#define PROJETPROGAVANCEE_PANEL_HPP

#include "gui/Entity.hpp"
#include "gui/Anchor.hpp"

#include <vector>
#include <memory>

namespace gui {

class Panel : public Entity {
public:
    using Ptr = std::shared_ptr<Panel>;

public:
    explicit Panel(std::shared_ptr<Gui> gui);
    ~Panel() override;

    [[nodiscard]] unsigned int getWidth() const override;
    void setWidth(int w);

    [[nodiscard]] unsigned int getHeight() const override;
    void setHeight(int h);

    [[nodiscard]] const Color& getColor() const;
    void setColor(const Color& c);

protected:
    void onRender(GUIRenderer& renderer) const override;

private:
    int width;
    int height;
    Color color;
};

}

#endif //PROJETPROGAVANCEE_PANEL_HPP
