//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_PHYSICS2D_H
#define DUST_PHYSICS2D_H

#include <vector>
#include <chrono>
#include <thread>
#include "ParticleSystem2D.h"

namespace Dust {
    class Physics2D {
    public:
        inline static bool doingPhysics = true;
        inline static Dust::ParticleSystem2D particlePhysics;
        explicit Physics2D() = default;

        static void startPhysics();

        static void PhysicsLoop();

        static void stopPhysics();

        static void clearParticles();

    private:
        inline static std::thread thread;

    };
}

#endif //DUST_PHYSICS2D_H
