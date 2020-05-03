#ifndef PROJETPROGAVANCEE_SHOT_HPP
#define PROJETPROGAVANCEE_SHOT_HPP

#include "Engine/Settings.hpp"
#include "Engine/Types/Vec2.hpp"

struct Shot {
    engine::Vec2f position;
    engine::Vec2f speed;

    bool update(double dt) {
        position += speed * dt;
        const auto& settings = engine::Settings::getInstance();
         return position.x() < 0
             || position.x() >= settings.getParameter<int>("window_width")
             || position.y() < 0
             || position.y() >= settings.getParameter<int>("window_height");
    }
};

#endif //PROJETPROGAVANCEE_SHOT_HPP
