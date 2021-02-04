//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_SIMPLEPHYSICS_H
#define DUST_SIMPLEPHYSICS_H

#include <vector>
#include <chrono>
#include <thread>
#include "ParticlePhysics.h"

namespace Dust {
    class SimplePhysics {
    public:
        inline static bool doingPhysics = true;
        inline static Dust::ParticlePhysics particlePhysics;
        explicit SimplePhysics() = default;

        static void startPhysics(){
            doingPhysics = true;
            thread =  std::thread(PhysicsLoop);
        }

        static void PhysicsLoop(){
            auto targetDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(physicsTimeStep)); //in microseconds
            auto deltaTimeMargin = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds((int)(physicsTimeStep*0.50))); //in microseconds
            std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();;
            std::chrono::time_point<std::chrono::steady_clock> nextPoint;
            while(doingPhysics){
                nextPoint = lastTime + targetDeltaTime;
                auto now = std::chrono::steady_clock::now();
                if(now >= nextPoint){
                    if(now >= nextPoint + deltaTimeMargin) Logger::info( (now - (nextPoint+deltaTimeMargin)).count(), "Physics loop lagged by (ns)");
                    lastTime = std::chrono::steady_clock::now();
                    particlePhysics.particleInteractions();
                }
            }
        }

        static void stopPhysics(){
            doingPhysics = false;
            thread.join();
        }

        static void clearParticles(){
            stopPhysics();
            particlePhysics.clearAll();
            startPhysics();
        }

    private:
        inline static std::thread thread;

    };
}

#endif //DUST_SIMPLEPHYSICS_H
