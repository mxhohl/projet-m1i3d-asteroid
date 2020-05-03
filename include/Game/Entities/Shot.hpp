#ifndef PROJETPROGAVANCEE_SHOT_HPP
#define PROJETPROGAVANCEE_SHOT_HPP

#include "Engine/Settings.hpp"
#include "Types/Vec2.hpp"

struct Shot {
    Vec2f position;
    Vec2f speed;

    bool update(double dt) {
        position += speed * dt;
        const auto& settings = Settings::getInstance();
         return position.x() < 0
             || position.x() >= settings.getParameter<int>("window_width")
             || position.y() < 0
             || position.y() >= settings.getParameter<int>("window_height");
    }
};

#endif //PROJETPROGAVANCEE_SHOT_HPP
