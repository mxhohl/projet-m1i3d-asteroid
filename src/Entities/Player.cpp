#include "Entities/Player.hpp"

#include <iostream>

Player::Player(const std::shared_ptr<PhysicEngine>& physicEngine) :
        shooting(false),
        shootTimer(SHOOT_RATE) {
    polygon = {
            {0, -2},
            {2, 2},
            {0, 1},
            {-2, 2}
    };

    setScale(5);
    setPosition({600, 700});

    forward = {0, -1};

    shots = std::make_shared<std::vector<Shot>>();
    physicEngine->setShots(shots);

    rotationDir = 0;

    accelerating = false;
    acceleration = Vec2f(0);
    speed = {0, 0};
}

void Player::update(Renderer& renderer) {
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

void Player::update(KeyboardEventData& data) {
    if (data.keycode == SDLK_z) {
        accelerating = data.type == KeyboardEventData::Press;
    } else if (data.keycode == SDLK_q) {
        if (data.type == KeyboardEventData::Press) {
            rotationDir = -1;
        } else {
            rotationDir = 0;
        }
    } else if (data.keycode == SDLK_d) {
        if (data.type == KeyboardEventData::Press) {
            rotationDir = +1;
        } else {
            rotationDir = 0;
        }
    } else if (data.keycode == SDLK_SPACE) {
        shooting = data.type == KeyboardEventData::Press;
        if (!shooting) {
            shootTimer = SHOOT_RATE;
        }
    }
}

void Player::update(double &dt) {
    if (shooting) {
        shootTimer += dt;

        if (shootTimer > SHOOT_RATE) {
            Vec2f bulletPos = Mat3<float>::rotation(
                    getRotation()).transformPoint({0, -12}
            );
            shots->push_back({
                getPosition() + bulletPos,
                forward * BULLET_SPEED
            });

            shootTimer -= SHOOT_RATE;
        }
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
    forward = Mat3f::rotation(getRotation()).transformPoint({0, -1});

    /* TEMPORARY CODE */
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
            if (speed.normalized() != normalised) {
                speed = Vec2f(0);
            }
        }
    }
    move(speed * dt);
}
