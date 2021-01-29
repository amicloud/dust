//
// Created by Amy on 12/31/2020.
//

#pragma once
#ifndef DUST_PARTICLE_H
#define DUST_PARTICLE_H

#include <cstdint>
#include "../Constants.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
namespace Dust {
    class Particle {

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

        explicit Particle(Vec2<double> _position, Flavor _flavor, ColorCharge _color = ColorCharge::BLACK, bool _isCopy = false) {
            isCopy= _isCopy;
            if(UUIDs.empty()){
                UUID = 0;
                UUIDs.emplace_back(UUID);
            } else {
                UUID = UUIDs.back() + 1 - ((int)isCopy);
                UUIDs.emplace_back(UUID);
            }
            position = Vec2(_position);
            switch(_flavor){
                case Flavor::UP:
                    mass = 2.2*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::TWO_THIRDS;
                    colorCharge = _color;
                    break;
                case Flavor::DOWN:
                    mass = 4.7*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    colorCharge = _color;
                    break;
                case Flavor::CHARM:
                    mass = 1275.0*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::TWO_THIRDS;
                    colorCharge = _color;
                    break;
                case Flavor::STRANGE:
                    mass = 96.0*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    colorCharge = _color;
                    break;
                case Flavor::TOP:
                    mass = 173100.0*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::TWO_THIRDS;
                    colorCharge = _color;
                    break;
                case Flavor::BOTTOM:
                    mass = 4180.0*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    colorCharge = _color;
                    break;
                case Flavor::ELECTRON:
                    mass = 0.51*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::NEGATIVE_ONE;
                    colorCharge = ColorCharge::BLACK;
                    break;
                case Flavor::MUON:
                    mass = 105.66*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::NEGATIVE_ONE_THIRD;
                    colorCharge = ColorCharge::BLACK;
                    break;
                case Flavor::TAU:
                    mass = 1776.8*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::TWO_THIRDS;
                    colorCharge = ColorCharge::BLACK;
                    break;
                case Flavor::ELECTRON_NEUTRINO:
                    mass = 0.0000001*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::ZERO;
                    colorCharge = ColorCharge::BLACK;
                    break;
                case Flavor::MUON_NEUTRINO:
                    mass = 0.17*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::ZERO;
                    colorCharge = ColorCharge::BLACK;
                    break;
                case Flavor::TAU_NEUTRINO:
                    mass = 18.2*massUnit;
                    spin = Spin::HALF;
                    charge = ElectricCharge::ZERO;
                    colorCharge = ColorCharge::BLACK;
                    break;
            }
            massInverse = 1/mass;
            flavor = _flavor;
        }

        void impartForce(Vec2<double> _forceVector){
            if(isnan(_forceVector.x) || isnan(_forceVector.y)){
                move();
                return;
            }
            velocity = velocity + (_forceVector * massInverse * lorentzFactor);
            if(velocity > speedOfLight){
                velocity = speedOfLight - std::numeric_limits<double>::epsilon();
            }
//            velocity.y += _forceVector.y * massInverse * lorentzFactor;
            lorentzFactor = getLorentzFactor(velocity);
//            std::cout << _forceVector.x << " ";
//            std::cout << _forceVector.y <<std::endl;
            move();
        }

        double distanceFrom(Vec2<double> _position){
            return sqrt(pow((_position.y - position.y),2)+pow(_position.x-position.x,2));
        }

        double getRelativisticMass(){
            return mass/lorentzFactor;
        }

        static double getLorentzFactor(Vec2<double> _velocity){
            double res = sqrt(1-(pow(abs(_velocity.x) + abs(_velocity.y),2)/speedOfLightSquared));
            if(isnan(res)){
                return 1;
            }
//            std::cout << res << std::endl;
            return res;
        }

        void move(){
            position = position + velocity;
//            printPosition();
        }

        void printPosition() const{
            std::cout << "pos" << position.x << ", " << position.y << std::endl;
        }

        ~Particle(){
            for(int i = 0; i < UUIDs.size(); i++){
                if(UUID == UUIDs.at(i)) {
                    UUIDs.erase(UUIDs.begin()+i);
                }
            }
        }
    };
}


#endif //DUST_PARTICLE_H
