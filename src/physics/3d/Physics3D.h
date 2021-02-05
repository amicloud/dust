//
// Created by Amy on 2/4/2021.
//

#ifndef DUST_PHYSICS3D_H
#define DUST_PHYSICS3D_H


#include <thread>
#include "ParticleSystem3D.h"

namespace Dust{
class Physics3D {
public:
    inline static bool doingPhysics = true;
    inline static Dust::ParticleSystem3D particlePhysics;
    explicit Physics3D() = default;

    static void startPhysics();

    static void PhysicsLoop();

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


#endif //DUST_PHYSICS3D_H
