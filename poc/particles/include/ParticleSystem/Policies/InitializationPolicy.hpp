#ifndef TESTSDLMIXER_INITIALIZATIONPOLICY_HPP
#define TESTSDLMIXER_INITIALIZATIONPOLICY_HPP

#include "../BaseParticle.hpp"

namespace ParticleSystem {

template<class ParticleType = BaseParticle>
class InitializationPolicy {
    static_assert(
            std::is_base_of<Particle,
                            ParticleType>::value,
            "ParticleType must inherit from Particle"
    );

public:
    virtual void initialize(ParticleType& particle) = 0;
};

}

#endif //TESTSDLMIXER_INITIALIZATIONPOLICY_HPP
