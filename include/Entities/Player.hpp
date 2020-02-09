#ifndef PROJETPROGAVANCEE_PLAYER_HPP
#define PROJETPROGAVANCEE_PLAYER_HPP

#include "Observer/Observer.hpp"
#include "Observer/KeyboardEventData.hpp"
#include "Rendering/Renderer.hpp"
#include "Transformable.hpp"

class Player : public Observer<Renderer>,
               public Observer<KeyboardEventData>,
               public Observer<double>,
               Transformable {
private:
    static constexpr float ROTATION_SPEED = 4.;
    static constexpr float MAX_SPEED = 80.;
    static constexpr float ACCELERATION_FACTOR = 80.;
    static constexpr float NATURAL_ACCELERATION_FACTOR = -10.;

public:
    Player();

    void update(Renderer& renderer) override;
    void update(KeyboardEventData& event) override;
    void update(double& deltaTime) override;

private:
    Polygon polygon;
    Vec2f forward;

    bool accelerating;
    Vec2f acceleration;
    Vec2f speed;

    int rotationDir;
};

#endif //PROJETPROGAVANCEE_PLAYER_HPP
