#ifndef PROJETPROGAVANCEE_ASTEROID_HPP
#define PROJETPROGAVANCEE_ASTEROID_HPP

#include "Engine/Physic/PhysicEntity.hpp"
#include "Engine/Types/Vec2.hpp"
#include "Engine/Types/Color.hpp"
#include "Engine/Types/Polygon.hpp"
#include "Player.hpp"

#include <random>

class Asteroid : public engine::PhysicEntity {
    friend class Asteroids;

public:
    struct RandomContext {
        RandomContext() :
                generator(engine::Settings::getInstance().getParameter<unsigned int>("seed")),
                speed_dist(-50, 50),
                posX_dist(0, engine::Settings::getInstance().getParameter<int>("window_width")),
                posY_dist(0, engine::Settings::getInstance().getParameter<int>("window_height")),
                color_dist(0, 5),
                scale_dist(0.8, 1.2) {}

        std::default_random_engine generator;
        std::uniform_real_distribution<float> speed_dist;
        std::uniform_int_distribution<int> posX_dist;
        std::uniform_int_distribution<int> posY_dist;
        std::uniform_int_distribution<int> color_dist;
        std::uniform_real_distribution<float> scale_dist;
    };

private:
    static constexpr float BASE_RADIUS = 15.f;
    static constexpr float MIN_PLAYER_DIST_ON_SPAWN = 100.f;

public:
    Asteroid();
    static Asteroid random(RandomContext& randomContext,
                           const std::shared_ptr<Player>& player = nullptr);

    static std::shared_ptr<Asteroid> fromExplosion(
            const std::shared_ptr<Asteroid>& parent,
            RandomContext& randomContext,
            const engine::Vec2f& position);

    void onCollide(engine::PhysicEngine::CollisionType collisionType,
                   [[maybe_unused]] engine::Vec2f position) override;

    [[nodiscard]] const engine::Color& getColor() const;
    void setColor(const engine::Color& col);

    [[nodiscard]] float getRadius() const;
    [[nodiscard]] int getSize() const;
    void setSize(int s);

    [[nodiscard]] engine::Circle getCircle() const;

private:
    int size;
    engine::Color color;

    bool exploding;

};

#endif //PROJETPROGAVANCEE_ASTEROID_HPP
