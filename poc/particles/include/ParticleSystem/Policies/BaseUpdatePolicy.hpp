#ifndef TESTSDLMIXER_BASEUPDATEPOLICY_HPP
#define TESTSDLMIXER_BASEUPDATEPOLICY_HPP

#include "UpdatePolicy.hpp"

namespace ParticleSystem {

class BaseUpdatePolicy : public UpdatePolicy<BaseParticle> {
public:
    bool update(double dt, BaseParticle& particle) override {
        particle.lifetime -= dt;
        if (particle.lifetime <= 0) {
            return false;
        }

        particle.position += particle.speed * dt;
        return true;
    }
};

}

#endif //TESTSDLMIXER_BASEUPDATEPOLICY_HPP
