//
// Created by Amy on 1/23/2021.
//

//#include "ParticleSystem2D.h"
#include "ParticleSystem2D.h"

void Dust::ParticleSystem2D::clearAll() {
    particles.clear();
    tempParticles.clear();
    particlesToAdd.clear();
    forRender.clear();
    forRenderTemp.clear();
}

void Dust::ParticleSystem2D::particleInteractions() {
    for (auto newParticle : particlesToAdd) {
        particles.emplace_back(
                new Particle2D(newParticle.position, newParticle.flavor, newParticle.colorCharge));
        tempParticles.emplace_back(
                new Particle2D(newParticle.position, newParticle.flavor, newParticle.colorCharge, true));
        forRender.push_back({newParticle.position.cast<float>()});
        forRenderTemp.push_back({newParticle.position.cast<float>()});
    }
    particlesToAdd.clear();
    maxSpeed = 0;
    forRenderTemp.clear();
    auto timer = new Logger::Timer(true);
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
            if (distance < 1) continue;
            particle->impartForce(vec * -1 * gravitationalConstant *
                                  (other->mass /
                                   distanceInDimensionsMinusOne));
            particle->impartForce(
                    (((vec * inverseDistanceMinus) + (particle->velocity.perpendicular() * (1+inverseDistanceMinus))) *
                     (particle->charge * other->charge)) * fineStructureConstant);

        }

        if (particle->lorentzFactor < maxSpeed) maxSpeed = particle->lorentzFactor;
        forRenderTemp.push_back({particle->position.cast<float>()});

    }
    delete timer;
    std::copy(particles.begin(), particles.end(), tempParticles.begin());
    std::copy(forRenderTemp.begin(), forRenderTemp.end(), forRender.begin());


}

void Dust::ParticleSystem2D::createParticle(Dust::ParticleSystem2D::ParticleInfo2D _particleInfo) {

    Logger::debug("creating a particle...");
    particlesToAdd.push_back(_particleInfo);


}

