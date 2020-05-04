#ifndef TESTSDLMIXER_UPDATEPOLICY_HPP
#define TESTSDLMIXER_UPDATEPOLICY_HPP

#include "../BaseParticle.hpp"

namespace ParticleSystem {

template<class ParticleType = BaseParticle>
class UpdatePolicy {
    static_assert(
            std::is_base_of<Particle,
                            ParticleType>::value,
            "ParticleType must inherit from Particle"
    );

public:
    virtual ~UpdatePolicy() = default;
    virtual bool update(double dt, ParticleType& particle) = 0;
};

}

#endif //TESTSDLMIXER_UPDATEPOLICY_HPP
