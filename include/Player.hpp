#ifndef PROJETPROGAVANCEE_PLAYER_HPP
#define PROJETPROGAVANCEE_PLAYER_HPP

#include <Observer/Observer.hpp>
#include "Rendering/Renderer.hpp"

class Player : public Observer<Renderer> {
public:
    Player();

    void update(Renderer& renderer) override;

private:
    Polygon polygon;
};

#endif //PROJETPROGAVANCEE_PLAYER_HPP
