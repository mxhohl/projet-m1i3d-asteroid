#include <iostream>
#include "Game/Entities/Asteroid.hpp"

#include "Engine/Settings.hpp"

Asteroid::Asteroid() : rotation_speed(0), size(1), exploding(false) {};

void Asteroid::onCollide(engine::PhysicEngine::CollisionType collisionType,
                         engine::Vec2f position) {
    if (exploding) {
        return;
    }

    if (collisionType == engine::PhysicEngine::CollisionType::WithShot) {
        exploding = true;
    } else if (collisionType == engine::PhysicEngine::CollisionType::WithAsteroid) {
        const auto bounceDirection =
                ((getPosition() - position).normalized()
                + getSpeed().normalized()).normalized();
        setSpeed(bounceDirection * getSpeed().length());
    }
}

Asteroid Asteroid::random(const std::shared_ptr<Player>& player) {
    static std::default_random_engine generator(
            engine::Settings::getInstance().getParameter<unsigned int>("seed")
    );

    static std::uniform_real_distribution<float> speed_dist(-50, 50);
    static std::uniform_real_distribution<float> rotation_spd_dist(-0.5, 0.5);
    static std::uniform_int_distribution<int> posX_dist(
            0,
            engine::Settings::getInstance().getParameter<int>("window_width")
    );
    static std::uniform_int_distribution<int> posY_dist(
            0,
            engine::Settings::getInstance().getParameter<int>("window_height")
    );
    static std::uniform_real_distribution<float> rotation_dist(0, 360);
    static std::uniform_int_distribution<int> color_dist(0, 5);
    static std::uniform_real_distribution<float> scale_dist(0.8, 1.2);

    Asteroid asteroid;
    asteroid.setSpeed({speed_dist(generator), speed_dist(generator)});
    asteroid.rotation_speed = rotation_spd_dist(generator);
    asteroid.setRotationDeg(rotation_dist(generator));
    asteroid.setScale(scale_dist(generator));

    engine::Vec2f position;
    do {
        position = engine::Vec2f(posX_dist(generator), posY_dist(generator));
    } while(player &&
            (player->getPosition() - position).length()
            < MIN_PLAYER_DIST_ON_SPAWN
    );
    asteroid.setPosition(position);

    asteroid.size = 2;
    asteroid.color = {
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            255
    };

    return asteroid;
}

const engine::Color& Asteroid::getColor() const {
    return color;
}

void Asteroid::setColor(const engine::Color& col) {
    color = col;
}

float Asteroid::getRadius() const {
    return float(size) * BASE_RADIUS;
}

int Asteroid::getSize() const {
    return size;
}

void Asteroid::setSize(int s) {
    size = s;
}

engine::Circle Asteroid::getCircle() const {
    return engine::Circle(static_cast<float>(getRadius()));
}
