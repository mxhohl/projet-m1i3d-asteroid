#ifndef TESTSDLMIXER_BASEINITIALIZATIONPOLICY_HPP
#define TESTSDLMIXER_BASEINITIALIZATIONPOLICY_HPP

#include "InitializationPolicy.hpp"

#include <random>

namespace ParticleSystem {

class BaseInitializationPolicy : public InitializationPolicy<BaseParticle> {
public:
    BaseInitializationPolicy() : speed(0),
                                 size(1),
                                 minLifetime(2),
                                 maxLifetime(5),
                                 generator(), /* TODO: seed */
                                 directionDist(0.f, 1.f),
                                 lifetimeDist(minLifetime, maxLifetime) {}

    void initialize(BaseParticle& particle) override {
        float directionRatio = directionDist(generator);
        particle.speed = directionRangeFirstEnd * directionRatio
                       + directionRangeSecondEnd * (1.f - directionRatio);
        particle.speed.normalize();
        particle.speed *= speed;

        particle.color = color;
        particle.size = size;

        particle.lifetime = lifetimeDist(generator);
    }

    [[nodiscard]] float getSpeed() const {
        return speed;
    }

    void setSpeed(float spd) {
        speed = spd;
    }

    [[nodiscard]] const engine::Vec2f& getDirectionRangeFirstEnd() const {
        return directionRangeFirstEnd;
    }

    void setDirectionRangeFirstEnd(const engine::Vec2f& direction) {
        directionRangeFirstEnd = direction;
    }

    [[nodiscard]] const engine::Vec2f& getDirectionRangeSecondEnd() const {
        return directionRangeSecondEnd;
    }

    void setDirectionRangeSecondEnd(const engine::Vec2f& direction) {
        directionRangeSecondEnd = direction;
    }

    [[nodiscard]] const engine::Color& getColor() const {
        return color;
    }

    void setColor(const engine::Color& col) {
        color = col;
    }

    [[nodiscard]] float getSize() const {
        return size;
    }

    void setSize(float s) {
        size = s;
    }

    [[nodiscard]] double getMinLifetime() const {
        return minLifetime;
    }

    void setMinLifetime(double min) {
        minLifetime = min;
        lifetimeDist = std::uniform_real_distribution<double>(
                minLifetime,
                maxLifetime
        );
    }

    [[nodiscard]] double getMaxLifetime() const {
        return maxLifetime;
    }

    void setMaxLifetime(double max) {
        maxLifetime = max;
        lifetimeDist = std::uniform_real_distribution<double>(
                minLifetime,
                maxLifetime
        );
    }

private:
    float speed;
    engine::Vec2f directionRangeFirstEnd;
    engine::Vec2f directionRangeSecondEnd;
    engine::Color color;
    float size;
    double minLifetime;
    double maxLifetime;

private:
    std::default_random_engine generator;
    std::uniform_real_distribution<float> directionDist;
    std::uniform_real_distribution<double> lifetimeDist;
};

}

#endif //TESTSDLMIXER_BASEINITIALIZATIONPOLICY_HPP
