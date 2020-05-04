#ifndef TESTSDLMIXER_PARTICLEEMITTER_HPP
#define TESTSDLMIXER_PARTICLEEMITTER_HPP

#include <type_traits>
#include <functional>

#include "Policies/UpdatePolicy.hpp"
#include "ParticleSystem/Policies/InitializationPolicy.hpp"

#include "Policies/BaseInitializationPolicy.hpp"
#include "Policies/BaseUpdatePolicy.hpp"

namespace ParticleSystem {

template<size_t maxParticles = 100000,
        class UpdatePolicyType = BaseUpdatePolicy,
        class InitializationPolicyType = BaseInitializationPolicy,
        class ParticleType = BaseParticle>
class ParticleEmitter {
    static_assert(
            std::is_base_of<Particle,
                    ParticleType>::value,
            "ParticleType must inherit from Particle"
    );

    static_assert(
            std::is_base_of<UpdatePolicy<ParticleType>,
                            UpdatePolicyType>::value,
            "UpdatePolicyType must inherit from Policy<ParticleType>"
    );

    static_assert(
            std::is_base_of<InitializationPolicy<ParticleType>,
                            InitializationPolicyType>::value,
            "InitializationPolicyType must inherit from "
            "InitializationPolicy<ParticleType>"
    );

public:
    UpdatePolicyType particleUpdater;
    InitializationPolicyType particleInitializer;

public:
    explicit ParticleEmitter(size_t emissionRate) :
            particleCount(0),
            emissionRate(emissionRate),
            emissionPeriod(1.f / emissionRate),
            emissionCounter(0) {
        particles = new ParticleType[maxParticles];
    }

    ~ParticleEmitter() {
        delete particles;
    }

    void update(double dt) {
        emissionCounter += dt;
        if (emissionCounter >= emissionPeriod) {
            const size_t count = std::floor(emissionCounter / emissionPeriod);
            emissionCounter -= count;
            emit(count);
        }

        for (size_t i = 0; i < particleCount;) {
            if (!particleUpdater.update(dt, particles[i])) {
                particles[i] = std::move(particles[particleCount - 1]);
                --particleCount;
            } else {
                ++i;
            }
        }
    }

    void draw() {
        for (size_t i = 0; i < particleCount; ++i) {
            drawParticle(particles[i]);
        }
    }

    void setDrawParticle(
            const std::function<void(const ParticleType&)>& function) {
        drawParticle = function;
    }

    [[nodiscard]] size_t getEmissionRate() const {
        return emissionRate;
    }

    void setEmissionRate(size_t rate) {
        emissionRate = rate;
        emissionPeriod = 1. / rate;
    }

    [[nodiscard]] const engine::Vec2f& getPosition() const {
        return position;
    }

    void setPosition(const engine::Vec2f& pos) {
        position = pos;
    }

private:
    void emit(size_t amount) {
        if (particleCount + amount > maxParticles) {
            amount = maxParticles - particleCount;
        }
        for (size_t i = 0; i < amount; ++i) {
            particles[i] = ParticleType();
            particles[i].position = position;
            particleInitializer.initialize(particles[i]);
            ++particleCount;
        }
    }

private:
    ParticleType* particles;
    size_t particleCount;
    std::function<void(const ParticleType&)> drawParticle;

    engine::Vec2f position;

    size_t emissionRate;
    double emissionPeriod;

    double emissionCounter;
};

}

#endif //TESTSDLMIXER_PARTICLEEMITTER_HPP
