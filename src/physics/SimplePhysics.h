//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_SIMPLEPHYSICS_H
#define DUST_SIMPLEPHYSICS_H

#include <vector>
#include <chrono>
#include <thread>
#include "ParticleSystem.h"

namespace Dust {
    class SimplePhysics {
    public:
        inline static bool doingPhysics = true;
        inline static Dust::ParticleSystem ParticleSystem;
        explicit SimplePhysics() = default;

        static void startPhysics(){
            doingPhysics = true;
            thread =  std::thread(PhysicsLoop);
        }

        static void PhysicsLoop(){
            auto targetDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::microseconds(physicsTimeStep)); //in microseconds
            std::chrono::time_point<std::chrono::steady_clock> lastTime;
            while(doingPhysics){
                std::chrono::time_point<std::chrono::steady_clock> nextPoint = lastTime + targetDeltaTime;
                if(std::chrono::steady_clock::now() >= nextPoint){
                    lastTime = std::chrono::steady_clock::now();
                    ParticleSystem.particleInteractions();
                }
            }
        }

        static void stopPhysics(){
            doingPhysics = false;
            thread.join();
        }

    private:
        inline static std::thread thread;

    };
}

#endif //DUST_SIMPLEPHYSICS_H
