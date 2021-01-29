//
// Created by Amy on 1/27/2021.
//
#pragma once
#ifndef DUST_HADRON_H
#define DUST_HADRON_H

#include "Particle.h"
#include <vector>

namespace Dust {
    class Hadron {
        std::vector<Particle *> particles;
        double charge;
        double restMass;
        explicit Hadron(std::vector<Particle *> _componentParticles){
            std::move(_componentParticles.begin(), _componentParticles.end(), particles.begin());
            for(auto p : particles){
                charge += p->charge;
                restMass += p->mass;
            }
        }

        void decay(){

        }


    };
}

#endif //DUST_HADRON_H
