#include <iostream>
#include "Game/Entities/Asteroid.hpp"

#include "Engine/Settings.hpp"

Asteroid::Asteroid() : size(1), exploding(false) {};

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

Asteroid Asteroid::random(RandomContext& randomContext,
                          const std::shared_ptr<Player>& player) {
    Asteroid asteroid;
    asteroid.setSpeed({
        randomContext.speed_dist(randomContext.generator),
        randomContext.speed_dist(randomContext.generator)
    });

    asteroid.setScale(randomContext.scale_dist(randomContext.generator));

    engine::Vec2f position;
    do {
        position = engine::Vec2f(
                randomContext.posX_dist(randomContext.generator),
                randomContext.posY_dist(randomContext.generator)
        );
    } while(player &&
            (player->getPosition() - position).length()
            < MIN_PLAYER_DIST_ON_SPAWN
    );
    asteroid.setPosition(position);

    asteroid.size = 2;
    asteroid.color = {
            static_cast<uint8_t>(
                    randomContext.color_dist(randomContext.generator) * 51
            ),
            static_cast<uint8_t>(
                    randomContext.color_dist(randomContext.generator) * 51
            ),
            static_cast<uint8_t>(
                    randomContext.color_dist(randomContext.generator) * 51
            ),
            255
    };

    return asteroid;
}

std::shared_ptr<Asteroid> Asteroid::fromExplosion(
        const std::shared_ptr<Asteroid> &parent,
        RandomContext& randomContext,
        const engine::Vec2f& position) {

    auto newAsteroid = std::make_shared<Asteroid>();
    newAsteroid->size = parent->size - 1;
    newAsteroid->color = parent->color;

    newAsteroid->setScale(randomContext.scale_dist(randomContext.generator));
    newAsteroid->setRotation(parent->getRotation());

    newAsteroid->setPosition(position);

    newAsteroid->setSpeed(
            parent->getSpeed()
            + (newAsteroid->getPosition() - parent->getPosition())
              * 2.f
    );

    return newAsteroid;
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
