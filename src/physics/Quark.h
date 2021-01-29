//
// Created by Amy on 1/24/2021.
//

#ifndef DUST_QUARK_H
#define DUST_QUARK_H
#include "Particle.h"
namespace Dust {
    class Quark : Particle {

        Flavor flavor;
    public:
        Quark(const Vec2<double> _position, Flavor _flavor) {
            position = _position;
            flavor = _flavor;
            double _mass;
            Spin _spin;
            ElectricCharge _charge;
            switch(_flavor){
                case Flavor::TOP:
                    _mass = 173210;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::TWO_THIRDS;
                    break;
                case Flavor::BOTTOM:
                    _mass = 4180;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    break;
                case Flavor::CHARM:
                    _mass = 1275;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::TWO_THIRDS;
                    break;
                case Flavor::STRANGE:
                    _mass = 95;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    break;
                case Flavor::TOP:
                    _mass = 2.3;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::TWO_THIRDS;
                    break;
                case Flavor::BOTTOM:
                    _mass = 4.8;
                    _spin = Spin::HALF;
                    _charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    break;
            }
            mass = _mass;
            spin = _spin;
            charge = _charge;
        }

    private:
}

#endif //DUST_QUARK_H
