//
// Created by Amy on 12/31/2020.
//

#pragma once
#ifndef DUST_PARTICLE2D_H
#define DUST_PARTICLE2D_H

#include <cstdint>
#include "Constants.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
namespace Dust {
    class Particle2D {

    public:
        double spin;
        static inline std::vector<uint32_t> UUIDs;
        uint32_t UUID;
        Vec2<double> position{};
        Vec2<double> velocity{std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
        double charge;
        ColorCharge colorCharge;
        double mass;
        double massInverse;
        double lorentzFactor = getLorentzFactor(velocity);
        bool isCopy;
        Flavor flavor;

        explicit Particle2D(Vec2<double> _position, Flavor _flavor, ColorCharge _color = ColorCharge::BLACK, bool _isCopy = false);

        void impartForce(Vec2<double> _forceVector);

        double distanceFrom(Vec2<double> _position);

        static double getLorentzFactor(Vec2<double> _velocity);

        void move();

        void printPosition() const;

        ~Particle2D();
    };
}


#endif //DUST_PARTICLE2D_H
