#include "Player.hpp"

Player::Player() {
    polygon = {
            {0, -2},
            {2, 2},
            {0, 1},
            {-2, 2}
    };

    setScale(5);
    setPosition({600, 700});

    forward = {0, -1};

    accelerating = false;
    acceleration = Vec2f(0);
    speed = {0, 0};

    rotationDir = 0;
}

void Player::update(Renderer& renderer) {
    renderer.setDrawColor({255, 255, 255, 255});
    renderer.drawPolygon(polygon, getTransformMatrix());

#ifdef DEBUG
    if (speed.sqrLength() > 0) {
        renderer.setDrawColor({0, 255, 0, 255});
        renderer.drawLine(
                getPosition(),
                getPosition() + speed,
                Mat3f::identity()
        );
    }

    renderer.setDrawColor({0, 0, 255, 255});
    renderer.drawLine(
            getPosition(),
            getPosition() + forward * 20.,
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
        /* TODO */
    }
}

void Player::update(double &deltaTime) {
    rotate(ROTATION_SPEED * float(rotationDir) * float(deltaTime));
    forward = Mat3f::rotation(getRotation()).transformPoint({0, -1});

    if (accelerating) {
        acceleration = forward * ACCELERATION_FACTOR;
        speed += acceleration * deltaTime;

        if (speed.sqrLength() > MAX_SPEED * MAX_SPEED) {
            speed.normalize();
            speed *= MAX_SPEED;
        }
    } else {
        if (speed.sqrLength() > 0) {
            const auto normalised = speed.normalized();
            speed += (normalised
                    * NATURAL_ACCELERATION_FACTOR
                    * deltaTime);
            if (speed.normalized() != normalised) {
                speed = Vec2f(0);
            }
        }
    }
    move(speed * deltaTime);
}
