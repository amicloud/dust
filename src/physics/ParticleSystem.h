//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_PARTICLESYSTEM_H
#define DUST_PARTICLESYSTEM_H

#include <utility>
#include <vector>
#include "Particle.h"
#include "Logger.h"

namespace Dust {
    class ParticleSystem {
        struct ParticleInfo {
            Vec2<double> position;
            Flavor flavor;
            ColorCharge colorCharge = ColorCharge::BLACK;
        };

    public:
        std::vector<Particle *> particles = {};
        std::vector<Particle *> tempParticles = {};
        std::vector<ParticleInfo> particlesToAdd = {};
        double maxSpeed = 1.0;
//        explicit ParticleSystem(){
//
//        }

        struct ParticleForRender {
            Vec2<float> position;
//            Color colorCharge;
        };

        double flatPacked[universeSizeY * universeSizeX];
        std::vector<ParticleForRender> forRender;
        std::vector<ParticleForRender> forRenderTemp;

        void clearAll() {
            particles.clear();
            tempParticles.clear();
            particlesToAdd.clear();
            forRender.clear();
            forRenderTemp.clear();
        }

        void particleInteractions() {
            for (auto newParticle : particlesToAdd) {
                particles.emplace_back(
                        new Particle(newParticle.position, newParticle.flavor, newParticle.colorCharge));
                tempParticles.emplace_back(
                        new Particle(newParticle.position, newParticle.flavor, newParticle.colorCharge, true));
                forRender.push_back({newParticle.position.cast<float>()});
                forRenderTemp.push_back({newParticle.position.cast<float>()});
            }
            particlesToAdd.clear();
            maxSpeed = 0;
            forRenderTemp.clear();
            for (auto particle: particles) {

                for (auto other: tempParticles) {
                    if (particle->UUID == other->UUID) {

                        continue;
                    }
                    double distance = particle->distanceFrom(other->position);
                    auto vec = ((particle->position) - (other->position));
                    double distanceInDimensions = pow(distance, dimensions - 1);
                    double inverseDistance = 1/distanceInDimensions;
                    vec.normalize();
                    if ((distance <= 5)) {// && (distance > .25)) {
                        if (distance <= 1) {
                            if (distance == 0) continue;
                            particle->impartForce(
                                    vec * -1 * strongInteraction *
                                    ((int) (particle->colorCharge * (other->colorCharge)) * inverseDistance));
                        } else {
                            particle->impartForce(
                                    vec * -1 * strongInteraction *
                                    ((int) (particle->colorCharge * (other->colorCharge)) * distanceInDimensions));
                        }
                    }

                    particle->impartForce(vec * -1 * gravitationalConstant *
                                          (other->mass /
                                                  distanceInDimensions));
                    particle->impartForce(
                            vec * fineStructureConstant * (particle->charge * other->charge) * inverseDistance);

//                         particle->impartForce(
//                                 vec  * weakInteraction * ((int)particle->colorCharge * (int)other->colorCharge / pow(distance, 3)));
//                    }


                }

                if (particle->lorentzFactor < maxSpeed) maxSpeed = particle->lorentzFactor;
                forRenderTemp.push_back({particle->position.cast<float>()});

            }
//            memcpy(particles.data(), tempParticles.data(), particles.size() * sizeof());
            std::copy(particles.begin(), particles.end(), tempParticles.begin());
            std::copy(forRenderTemp.begin(), forRenderTemp.end(), forRender.begin());

        }


        void createParticle(ParticleInfo _particleInfo) {
            Logger::debug("creating a particle...");
            particlesToAdd.push_back(_particleInfo);

        }

    };
}

#endif //DUST_PARTICLESYSTEM_H

