//
// Created by Amy on 1/23/2021.
//
#pragma once
#ifndef DUST_PARTICLEPHYSICS_H
#define DUST_PARTICLEPHYSICS_H

#include <utility>
#include <vector>
#include "Particle.h"
#include "Logger.h"

namespace Dust {
    class ParticlePhysics {
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
//        explicit ParticlePhysics(){
//
//        }

        struct ParticleForRender {
            Vec2<float> position;
//            Color colorCharge;
        };

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
                    auto vec = particle->position - other->position;
                    double distanceInDimensionsMinusOne = pow(distance, dimensions - 1);
                    double inverseDistanceMinus = 1 / distanceInDimensionsMinusOne;
                    double distanceInDimensionsPlusOne = pow(distance, dimensions + 1);
                    double inverseDistancePlus = 1 / distanceInDimensionsPlusOne;
                    double relativeVelocity = (particle->velocity - other->velocity).magnitude();
//                    Logger::debug(relativeVelocity);
                    vec.normalize();
                    if (distance <= 1) {
                        particle->impartForce(
                                vec * (distance < 0.1 ? 1 : -1) * strongInteraction *
                                ((int) (particle->colorCharge * (other->colorCharge)) * inverseDistanceMinus));
                    } else {
                        particle->impartForce(
                                vec * -1 * strongInteraction *
                                ((int) (particle->colorCharge * (other->colorCharge)) * inverseDistancePlus));
                    }
                    if(distance < 1) continue;
                    particle->impartForce(vec * -1 * gravitationalConstant *
                                          (other->mass /
                                           distanceInDimensionsMinusOne));
                    particle->impartForce(//(vec + (vec.perpendicular() * (particle->charge * other->charge) * (particle->velocity - other->velocity).magnitude()))
                            ((vec + (particle->velocity.perpendicular() * (inverseDistanceMinus/relativeVelocity))) * (particle->charge * other->charge)) * fineStructureConstant * inverseDistanceMinus);
//                    particle->impartForce((vec.perpendicular() * (particle->charge * other->charge) * relativeVelocity*1e3) * fineStructureConstant * inverseDistanceMinus);

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

#endif //DUST_PARTICLEPHYSICS_H

