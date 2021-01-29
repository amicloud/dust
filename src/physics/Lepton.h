//
// Created by Amy on 1/24/2021.
//

#ifndef DUST_LEPTON_H
#define DUST_LEPTON_H
#include "Particle.h"

namespace Dust{
class Lepton : Particle {
    enum class Flavor{

    };
    Flavor flavor;
    Lepton(Vec2<double> _position, Flavor _flavor) {
        position = _position;

    }
};

}

#endif //DUST_LEPTON_H
