#ifndef PROJETPROGAVANCEE_GUI_HPP
#define PROJETPROGAVANCEE_GUI_HPP

#include "Observer/Observer.hpp"
#include "Entity.hpp"

#include <memory>
#include <unordered_map>

namespace gui {

class Gui : public Renderable {
public:
    Gui();
    ~Gui();

    template <class T>
    typename std::enable_if_t<std::is_base_of_v<Entity, T>, std::shared_ptr<T>>
    create() {
        uint32_t uid = uidCount++;
        auto newEntity = std::make_shared<T>(uid);

        entities[uid] = newEntity;
        return newEntity;
    }

    void update(Renderer& renderer) override;

private:
    uint32_t uidCount;
    std::unordered_map<uint32_t, std::shared_ptr<Entity>> entities;

};

}

#endif //PROJETPROGAVANCEE_GUI_HPP
