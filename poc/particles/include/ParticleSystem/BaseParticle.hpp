#ifndef TESTSDLMIXER_BASEPARTICLE_HPP
#define TESTSDLMIXER_BASEPARTICLE_HPP

#include <utility>

#include "Engine/Types/Vec2.hpp"
#include "Engine/Types/Color.hpp"
#include "Particle.hpp"

namespace ParticleSystem {

struct BaseParticle : public Particle {
    engine::Vec2f speed;
    engine::Color color;
    float size;
    double lifetime;
};

}

#endif //TESTSDLMIXER_BASEPARTICLE_HPP
