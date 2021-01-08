//
// Created by Amy on 12/31/2020.
//

#ifndef DUST_PARTICLE_H
#define DUST_PARTICLE_H
#pragma once

#include <cstdint>
#include "Element.h"

namespace Dust {
    class Particle {
        uint32_t x;
        uint32_t y;
        uint32_t z;
        Element type{};
    public:
        Particle(uint32_t i, uint32_t i1, uint32_t i2, Element color) : x(i), y(i1), z(i2), type() {}
    };
}


#endif //DUST_PARTICLE_H
