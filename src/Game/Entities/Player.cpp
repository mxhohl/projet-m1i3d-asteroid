#include "Game/Entities/Player.hpp"

#include <iostream>
#include "Game/Game.hpp"

Player::Player(const std::shared_ptr<engine::PhysicEngine>& physicEngine) :
        shooting(false),
        shootTimer(SHOOT_RATE) {
    polygon = {
            {0, -2},
            {2, 2},
            {0, 1},
            {-2, 2}
    };

    forward = {0, -1};

    shots = std::make_shared<std::vector<Shot>>();
    physicEngine->setShots(shots);

    rotationDir = 0;

    accelerating = false;
    acceleration = engine::Vec2f(0);
    speed = {0, 0};
}

engine::Vec2f Player::getAbsoluteCollidePoint(size_t i) {
    if (i == 0) {
        return getTransformMatrix().transformPoint({0, -2});
    } else if (i == 1) {
        return getTransformMatrix().transformPoint({2, 2});
    } else if (i == 2) {
        return getTransformMatrix().transformPoint({-2, 2});
    } else {
        return {-1, -1};
    }
}

void Player::update(engine::Renderer& renderer) {
    renderer.setDrawColor({255, 255, 255, 255});
    renderer.draw(polygon, getTransformMatrix());

    for (auto& shot : *shots) {
        renderer.draw(shot.position);
    }

#ifdef DEBUG
    if (speed.sqrLength() > 0) {
        renderer.setDrawColor({0, 255, 0, 255});
        renderer.draw(
                getPosition(),
                getPosition() + speed,
                Mat3f::identity()
        );
    }

    renderer.setDrawColor({0, 0, 255, 255});
    renderer.draw(
            getPosition(),
            getPosition() + forward * ACCELERATION_FACTOR,
            Mat3f::identity()
    );
#endif
}

void Player::update(const engine::KeyboardEventData& data) {
    if (data.keycode == SDLK_z) {
        accelerating = data.type == engine::KeyboardEventData::Press;
    } else if (data.keycode == SDLK_q) {
        if (data.type == engine::KeyboardEventData::Press) {
            rotationDir = -1;
        } else {
            rotationDir = 0;
        }
    } else if (data.keycode == SDLK_d) {
        if (data.type == engine::KeyboardEventData::Press) {
            rotationDir = +1;
        } else {
            rotationDir = 0;
        }
    } else if (data.keycode == SDLK_SPACE) {
        shooting = data.type == engine::KeyboardEventData::Press;
    }
}

void Player::update(double dt) {
    if (shooting) {
        shootTimer += dt;

        if (shootTimer > SHOOT_RATE) {
            engine::Vec2f bulletPos = engine::Mat3<float>::rotation(
                    getRotation()).transformPoint({0, -12}
            );
            shots->push_back({
                getPosition() + bulletPos,
                forward * BULLET_SPEED
            });

            shootTimer -= SHOOT_RATE;
        }
    } else if (shootTimer > SHOOT_RATE) {
        shootTimer = SHOOT_RATE;
    } else if (shootTimer != SHOOT_RATE) {
        shootTimer += dt;
    }

    auto it = shots->begin();
    while (it != shots->end()) {
        if (it->update(dt)) {
            it = shots->erase(it);
        } else {
            ++it;
        }
    }

    rotate(ROTATION_SPEED * float(rotationDir) * float(dt));
    forward = engine::Mat3f::rotation(getRotation()).transformPoint({0, -1});

    if (accelerating) {
        acceleration = forward * ACCELERATION_FACTOR;
        speed += acceleration * dt;

        if (speed.sqrLength() > MAX_SPEED * MAX_SPEED) {
            speed.normalize();
            speed *= MAX_SPEED;
        }
    } else {
        if (speed.sqrLength() > 0) {
            const auto normalised = speed.normalized();
            speed += (normalised
                      * NATURAL_ACCELERATION_FACTOR
                      * dt);
        }
    }
    move(speed * dt);
}

void Player::reset() {
    shots->clear();
    shooting = false;
    shootTimer = SHOOT_RATE;
    rotationDir = 0;
    accelerating = false;
    acceleration = engine::Vec2f(0);
    speed = {0, 0};
    setRotation(0);
}

void Player::onCollide() {
    Game::getInstance().endGame();
}
