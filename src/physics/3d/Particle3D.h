//
// Created by Amy on 2/4/2021.
//

#ifndef DUST_PARTICLE3D_H
#define DUST_PARTICLE3D_H


#include <vector>
#include <Constants.h>
#include <iostream>
#include "Vector3.h"

namespace Dust {
    class Particle3D {

    public:
        double spin;
        static inline std::vector<uint32_t> UUIDs;
        uint32_t UUID;
        Vector3<double> position{};
        Vector3<double> velocity{std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon()};
        double charge;
        ColorCharge colorCharge;
        double mass;
        double massInverse;
        double lorentzFactor = getLorentzFactor(velocity);
        bool isCopy;
        Flavor flavor;

        explicit Particle3D(Vector3<double> _position, Flavor _flavor, ColorCharge _color = ColorCharge::BLACK, bool _isCopy = false);

        void impartForce(Vector3<double> _forceVector);

        double distanceFrom(Vector3<double> _position);

        double getRelativisticMass();

        static double getLorentzFactor(Vector3<double> _velocity);

        void move();

        void printPosition() const {
            std::cout << "pos" << position.x << ", " << position.y <<  ", " << position.z << std::endl;
        }

        ~Particle3D();
    };
}


#endif //DUST_PARTICLE3D_H
