//
// Created by Amy on 12/30/2020.
//

#ifndef DUST_DUST_H
#define DUST_DUST_H
#pragma once
#endif //DUST_DUST_H
#include "Particle.h"
#include "Renderer.h"
#include "Physics.h"
#include "Logger.h"


namespace Dust {
    class Dust {
    private:
        Renderer* renderer;
        std::vector<Particle>* particles;
    public:
        Dust(Renderer *renderer, std::vector<Particle>* particles) : renderer(renderer), particles(particles) {
//            renderer = new Renderer();
        };

        int update(){
            return renderer->draw();
        }
    };
}