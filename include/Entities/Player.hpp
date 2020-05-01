#ifndef PROJETPROGAVANCEE_PLAYER_HPP
#define PROJETPROGAVANCEE_PLAYER_HPP

#include "Physic/PhysicEngine.hpp"
#include "Observer/Observer.hpp"
#include "Observer/KeyboardEventData.hpp"
#include "Rendering/Renderer.hpp"
#include "Transformable.hpp"
#include "Shot.hpp"

class Player : public Renderable,
               public KeyboardObserver,
               public Updatable,
               public Transformable {
private:
    static constexpr float ROTATION_SPEED = 4.;
    static constexpr float MAX_SPEED = 90.;
    static constexpr float ACCELERATION_FACTOR = 80.;
    static constexpr float NATURAL_ACCELERATION_FACTOR = -20.;
    static constexpr float BULLET_SPEED = 200.;
    static constexpr float SHOOT_RATE = 0.5;

public:
    explicit Player(const std::shared_ptr<PhysicEngine>& physicEngine);

    [[nodiscard]] Vec2f getAbsoluteCollidePoint(size_t i);

    void update(Renderer& renderer) override;
    void update(const KeyboardEventData& event) override;
    void update(double dt) override;

    void onCollide();

private:
    Polygon polygon;
    Vec2f forward;

    bool accelerating;
    Vec2f acceleration;
    Vec2f speed;

    int rotationDir;

    bool shooting;
    double shootTimer;
    std::shared_ptr<std::vector<Shot>> shots;
};

#endif //PROJETPROGAVANCEE_PLAYER_HPP
