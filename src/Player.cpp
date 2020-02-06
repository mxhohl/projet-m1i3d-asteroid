#include "Player.hpp"

void Player::update(Renderer& renderer) {

    auto points = std::vector<Vec2f>{
            {2, 0}, {4, 4}, {2, 3}, {0, 4}
    };

    renderer.setDrawColor({255, 255, 255, 255});
    for (size_t i = 0; i < points.size(); ++i) {
        renderer.drawLine(points[i] * 5, points[(i + 1) % points.size()] * 5);
    }
}
