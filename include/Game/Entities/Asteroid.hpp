#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Engine/Physic/PhysicEntity.hpp"
#include "Engine/Types/Vec2.hpp"
#include "Engine/Types/Color.hpp"
#include "Engine/Rendering/Polygon.hpp"
#include "Player.hpp"

#include <random>

class Asteroid : public engine::PhysicEntity {
    friend class Asteroids;

private:
    static constexpr float BASE_RADIUS = 15.f;
    static constexpr float MIN_PLAYER_DIST_ON_SPAWN = 100.f;

public:
    Asteroid();
    static Asteroid random(const std::shared_ptr<Player>& player = nullptr);

    void onCollide(engine::PhysicEngine::CollisionType collisionType,
                   [[maybe_unused]] engine::Vec2f position) override;

    [[nodiscard]] const engine::Color& getColor() const;
    void setColor(const engine::Color& col);

    [[nodiscard]] float getRadius() const;
    [[nodiscard]] int getSize() const;
    void setSize(int s);

    [[nodiscard]] engine::Circle getCircle() const;

private:
    float rotation_speed;
    int size;
    engine::Color color;

    bool exploding;

};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
