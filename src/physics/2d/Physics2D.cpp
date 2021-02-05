//
// Created by Amy on 1/23/2021.
//

//#include "Physics2D.h"
#include "Physics2D.h"

void Dust::Physics2D::startPhysics() {
    doingPhysics = true;
    thread =  std::thread(PhysicsLoop);
}

void Dust::Physics2D::PhysicsLoop() {
    auto targetDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(physicsTimeStep)); //in microseconds
    std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();;
    std::chrono::time_point<std::chrono::steady_clock> nextPoint;
    while(doingPhysics){
        if(std::chrono::steady_clock::now() >= lastTime + targetDeltaTime){
            lastTime = std::chrono::steady_clock::now();
            particlePhysics.particleInteractions();
        }
    }
}

void Dust::Physics2D::stopPhysics() {
    doingPhysics = false;
    thread.join();
}

void Dust::Physics2D::clearParticles() {
    stopPhysics();
    particlePhysics.clearAll();
    startPhysics();
}

