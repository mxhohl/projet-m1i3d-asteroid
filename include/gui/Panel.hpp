#ifndef PROJETPROGAVANCEE_PANEL_HPP
#define PROJETPROGAVANCEE_PANEL_HPP

#include "Entity.hpp"
#include "Anchor.hpp"

#include <vector>
#include <memory>

namespace gui {

class Panel {
public:
    Panel();

    void addEntity(Anchor anchor, std::shared_ptr<Entity> entity);

private:
    std::vector<std::pair<Anchor, std::shared_ptr<Entity>>> elements;
};

}

#endif //PROJETPROGAVANCEE_PANEL_HPP
