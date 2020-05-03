#ifndef PROJETPROGAVANCEE_GUIRENDERER_HPP
#define PROJETPROGAVANCEE_GUIRENDERER_HPP

#include "Engine/Rendering/Renderer.hpp"

namespace gui {

class GUIRenderer {
public:
    GUIRenderer(Renderer& renderer, Vec2i currentDPos);
    GUIRenderer(const GUIRenderer& parent, Vec2i position);

    void setDrawColor(const Color& color);
    [[nodiscard]] Color getDrawColor() const;

    void draw(const Vec2i& start, const Vec2i& end);
    void draw(const RectI& rect);

private:
    Renderer& renderer;
    Vec2i currentDPos;

};

}

#endif //PROJETPROGAVANCEE_GUIRENDERER_HPP
