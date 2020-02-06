#include "Player.hpp"

Player::Player() {
    polygon = {
            {2, 0},
            {4, 4},
            {2, 3},
            {0, 4}
    };
    polygon.setScale(5);
    polygon.setPosition({100, 100});
}

void Player::update(Renderer& renderer) {
    renderer.setDrawColor({255, 255, 255, 255});
    renderer.drawPolygon(polygon);
}
