#include <iostream>
#include "Entities/Asteroid.hpp"

#include "Settings.hpp"

Asteroid::Asteroid() : rotation_speed(0) {};

void Asteroid::onCollide(PhysicEngine::CollisionType collisionType) {
    if (collisionType == PhysicEngine::CollisionType::WithShot) {
        if (size <= 0) {
            /* TODO: destruct this */
        } else {
            /* TODO: explode in multiple smaller */
        }
        std::cout << "COLLIDE" << std::endl;
    }
}

Asteroid Asteroid::random() {
    static std::default_random_engine generator(
            Settings::getInstance().getParameter<unsigned int>("seed")
    );

    static std::uniform_real_distribution<float> speed_dist(-50, 50);
    static std::uniform_real_distribution<float> rotation_spd_dist(-0.5, 0.5);
    static std::uniform_int_distribution<int> posX_dist(
            0,
            Settings::getInstance().getParameter<int>("window_width")
    );
    static std::uniform_int_distribution<int> posY_dist(
            0,
            Settings::getInstance().getParameter<int>("window_height")
    );
    static std::uniform_real_distribution<float> rotation_dist(0, 360);
    static std::uniform_int_distribution<int> color_dist(0, 5);
    static std::uniform_real_distribution<float> scale_dist(10, 20);

    Asteroid asteroid;
    asteroid.setSpeed({speed_dist(generator), speed_dist(generator)});
    asteroid.rotation_speed = rotation_spd_dist(generator);
    asteroid.setPosition(Vec2f(posX_dist(generator), posY_dist(generator)));
    asteroid.setRotationDeg(rotation_dist(generator));
    asteroid.setScale(scale_dist(generator));

    asteroid.size = 2;
    asteroid.color = {
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            255
    };

    return asteroid;
}

const Color& Asteroid::getColor() const {
    return color;
}

void Asteroid::setColor(const Color& col) {
    color = col;
}

float Asteroid::getRadius() const {
    return size * BASE_RADIUS;
}

int Asteroid::getSize() const {
    return size;
}

void Asteroid::setSize(int s) {
    size = s;
}

Circle Asteroid::getCircle() const {
    return Circle(getSize());
}
