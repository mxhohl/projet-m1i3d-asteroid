#ifndef PROJETPROGAVANCEE_PLAYER_HPP
#define PROJETPROGAVANCEE_PLAYER_HPP

#include "Engine/Physic/PhysicEngine.hpp"
#include "Engine/Observer/Observer.hpp"
#include "Engine/Observer/KeyboardEventData.hpp"
#include "Engine/Rendering/Renderer.hpp"
#include "Engine/Transformable.hpp"
#include "Shot.hpp"

class Player : public engine::Renderable,
               public engine::KeyboardObserver,
               public engine::Updatable,
               public engine::Transformable {
private:
    static constexpr float ROTATION_SPEED = 4.;
    static constexpr float MAX_SPEED = 90.;
    static constexpr float ACCELERATION_FACTOR = 80.;
    static constexpr float NATURAL_ACCELERATION_FACTOR = -20.;
    static constexpr float BULLET_SPEED = 200.;
    static constexpr float SHOOT_RATE = 0.5;

public:
    explicit Player(const std::shared_ptr<engine::PhysicEngine>& physicEngine);

    [[nodiscard]] engine::Vec2f getAbsoluteCollidePoint(size_t i);

    void update(engine::Renderer& renderer) override;
    void update(const engine::KeyboardEventData& event) override;
    void update(double dt) override;

    void reset();

    void onCollide();

private:
    engine::Polygon polygon;
    engine::Vec2f forward;

    bool accelerating;
    engine::Vec2f acceleration;
    engine::Vec2f speed;

    int rotationDir;

    bool shooting;
    double shootTimer;
    std::shared_ptr<std::vector<Shot>> shots;
};

#endif //PROJETPROGAVANCEE_PLAYER_HPP
