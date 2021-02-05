//
// Created by Amy on 2/4/2021.
//

#include "Particle3D.h"

void Dust::Particle3D::impartForce(Vector3<double> _forceVector) {

}

double Dust::Particle3D::distanceFrom(Vector3<double> _position) {
    return 0;
}

double Dust::Particle3D::getRelativisticMass() {
    return 0;
}

double Dust::Particle3D::getLorentzFactor(Vector3<double> _velocity) {
    return 0;
}

void Dust::Particle3D::move() {

}

Dust::Particle3D::Particle3D(Vector3<double> _position, Flavor _flavor, ColorCharge _color, bool _isCopy) {
    isCopy= _isCopy;
    if(UUIDs.empty()){
        UUID = 0;
        UUIDs.emplace_back(UUID);
    } else {
        UUID = UUIDs.back() + 1 - ((int)isCopy);
        UUIDs.emplace_back(UUID);
    }
    position = Vector3(_position);
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
        case Flavor::PROTON:
            mass = 938.272*massUnit;
            spin = Spin::HALF;
            charge = ElectricCharge::ONE;
            colorCharge = ColorCharge::WHITE;
            break;
        case Flavor::NEUTRON:
            mass = 939.565*massUnit;
            spin = Spin::HALF;
            charge = ElectricCharge::ZERO;
            colorCharge = ColorCharge::WHITE;
            break;
    }
    massInverse = 1/mass;
    flavor = _flavor;
}

Dust::Particle3D::~Particle3D() {
    for(int i = 0; i < UUIDs.size(); i++){
        if(UUID == UUIDs.at(i)) {
            UUIDs.erase(UUIDs.begin()+i);
        }
    }
}
