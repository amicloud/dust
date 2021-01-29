//
// Created by Amy on 12/31/2020.
//
#pragma once
#ifndef DUST_PHYSICS_H
#define DUST_PHYSICS_H

#include "../Constants.h"
#include "../../dependencies/catch.hpp"
#include "Field.h"
#include <chrono>
#include "Particle.h"

namespace Dust {

//    class Physics {
//        Field gravity{1, 1.0};
//        Field strong{1, 0.01};
//        Field electric{1, 0.1};
////        Field strong{};
//        std::vector<Dust::Particle> *particles;
//        Logger::Timer fieldAverageTimer = Logger::Timer(false, "Field propagation average.");
//
//    public:
//        explicit Physics(std::vector<Dust::Particle> *_particles) {
//            particles = _particles;
//            fieldAverageTimer.reset();
//        }
//
//        std::vector<Field> tick() {
//            auto tickTimer = new Logger::Timer(true, "Tick timer");
//            gravity.propagate();
//            strong.propagate();
//            electric.propagate();
//            for (auto particle : *particles) {
//                gravity.addMagnitude(particle.restMass, particle.position);
////                strong.addMagnitude(particle.hypercharge, particle.position);
////                electric.addMagnitude(particle.charge, particle.position);
//                particle.impartForce(gravity.getVectorAtPosition(particle.position) * gravitationalConstant);
////                particle.impartForce(strong.getVectorAtPosition(particle.position) * strongInteraction);
////                particle.impartForce(electric.getVectorAtPosition(particle.position) * fineStructureConstant);
//            }
////            fieldAverageTimer.tick();
////            fieldAverageTimer.printAverage();
//            delete tickTimer;
//            return {gravity, strong, electric};
//        }
//
//    private:
//
//
//    };
}

//TEST_CASE();

#endif //DUST_PHYSICS_H
