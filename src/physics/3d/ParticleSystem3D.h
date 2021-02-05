//
// Created by Amy on 2/4/2021.
//

#ifndef DUST_PARTICLESYSTEM3D_H
#define DUST_PARTICLESYSTEM3D_H


#include <vector>
#include <Constants.h>
#include "Particle3D.h"
#include "Vector3.h"
namespace Dust {
    class ParticleSystem3D {
        struct ParticleInfo3D {
            Vec2<double> position;
            Flavor flavor;
            ColorCharge colorCharge = ColorCharge::BLACK;
        };

    public:
        std::vector<Particle3D *> particles = {};
        std::vector<Particle3D *> tempParticles = {};
        std::vector<ParticleInfo3D> particlesToAdd = {};
        double maxSpeed = 1.0;


        struct ParticleForRender3D {
            Vector3<float> position;

        };

        std::vector<ParticleForRender3D> forRender;
        std::vector<ParticleForRender3D> forRenderTemp;

        void clearAll();

        void particleInteractions();


        void createParticle(ParticleInfo3D _particleInfo);

        explicit ParticleSystem3D();
    };

}


#endif //DUST_PARTICLESYSTEM3D_H
