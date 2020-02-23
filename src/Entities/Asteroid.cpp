#include <iostream>
#include "Entities/Asteroid.hpp"

#include "Settings.hpp"

Asteroid::Asteroid() : rotation_speed(0) {};

void Asteroid::onCollide(PhysicEngine::CollisionType collisionType) {
    if (collisionType == PhysicEngine::CollisionType::WithAsteroid) {
        // TODO: destruct this asteroid
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

    asteroid.color = {
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            static_cast<uint8_t>(color_dist(generator) * 51),
            255
    };

    asteroid.generatePolygon(generator);

    return asteroid;
}

void Asteroid::generatePolygon(std::default_random_engine generator) {
    static std::uniform_real_distribution<float> displacement_dist(-0.3, 0.3);

    constexpr int points_count = 7;

    Vec2f vec = {1, 0, 0};
    auto rotation = Mat3f::rotation(M_PI * 2.0 / float(points_count));

    for (int i = 0; i < points_count; ++i) {
        polygon.addPoint(
                vec + Vec2f{displacement_dist(generator),
                            displacement_dist(generator)}
        );
        vec = rotation.transformPoint(vec);
    }

}

Polygon Asteroid::getPolygon() const {
    return polygon;
}

const Color& Asteroid::getColor() const {
    return color;
}

void Asteroid::setColor(const Color& col) {
    color = col;
}
