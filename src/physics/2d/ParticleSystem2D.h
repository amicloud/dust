//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_PARTICLESYSTEM2D_H
#define DUST_PARTICLESYSTEM2D_H

#include <utility>
#include <vector>
#include "Particle2D.h"
#include "Logger.h"

namespace Dust {
    class ParticleSystem2D {
        struct ParticleInfo2D {
            Vec2<double> position;
            Flavor flavor;
            ColorCharge colorCharge = ColorCharge::BLACK;
        };

    public:
        std::vector<Particle2D *> particles = {};
        std::vector<Particle2D *> tempParticles = {};
        std::vector<ParticleInfo2D> particlesToAdd = {};
        double maxSpeed = 1.0;

        struct ParticleForRender {
            Vec2<float> position;
        };

        std::vector<ParticleForRender> forRender;
        std::vector<ParticleForRender> forRenderTemp;

        void clearAll();

        void particleInteractions();


        void createParticle(ParticleInfo2D _particleInfo);

    };
}

#endif //DUST_PARTICLESYSTEM2D_H

