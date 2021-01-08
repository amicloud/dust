#include <iostream>
#include <vector>
#include "Dust.h"
//#define log(x) Dust::Logging::log(x)
#define GLEW_STATIC 1
#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//using namespace Dust;

int main() {
    Dust::Color oxygen_color = Dust::Color();
    oxygen_color.a = 1.0;
    oxygen_color.b = 1.0;
    oxygen_color.r = 0.1;
    oxygen_color.g = 0.1;
    Dust::Element element = Dust::Element("Oxygen", &oxygen_color, 1);
    Dust::Particle particle = Dust::Particle(0, 1, 2, element);
    std::vector<Dust::Particle> particles;
    particles.push_back(particle);
    Dust::Renderer renderer = Dust::Renderer(600, 600, "Dust", &particles);
    Dust::Dust dust = Dust::Dust(&renderer, &particles);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    Logger::log("Testing!");
    while (true) {
        if(!dust.update()){
            return 0;
        };
    };
#pragma clang diagnostic pop
}