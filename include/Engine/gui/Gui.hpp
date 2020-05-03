#ifndef PROJETPROGAVANCEE_GUI_HPP
#define PROJETPROGAVANCEE_GUI_HPP

#include "Engine/Observer/Observer.hpp"
#include "Entity.hpp"

#include <memory>
#include <vector>

namespace gui {

class Gui : public Renderable, public std::enable_shared_from_this<Gui> {
    friend class Entity;

public:
    Gui();
    ~Gui() override;

    template <class T>
    typename std::enable_if_t<std::is_base_of_v<Entity, T>, std::shared_ptr<T>>
    create(std::shared_ptr<Entity> parent = nullptr) {
        auto newEntity = std::make_shared<T>(shared_from_this());
        newEntity->setNewParent(parent);

        return newEntity;
    }

    void update(Renderer& renderer) override;

private:
    std::vector<std::shared_ptr<Entity>> children;

};

}

#endif //PROJETPROGAVANCEE_GUI_HPP
