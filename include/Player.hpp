#ifndef PROJETPROGAVANCEE_PLAYER_HPP
#define PROJETPROGAVANCEE_PLAYER_HPP

#include <Observer/Observer.hpp>
#include "Renderer.hpp"

class Player : public Observer<Renderer> {
public:
    void update(Renderer& renderer) override;

private:

};

#endif //PROJETPROGAVANCEE_PLAYER_HPP
