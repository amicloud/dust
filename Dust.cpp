#include <iostream>
#include <vector>
#include "Dust.h"
//#define log(x) Dust::Logging::log(x)
#define GLEW_STATIC 1

#include "Renderer.h"
#include "Physics.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "catch.hpp"
//using namespace Dust;
#include "Constants.h"
Dust::Renderer renderer;
std::vector<Dust::Particle> particles;
Dust::Physics physics;
int update(){

    return renderer.draw();
}

int main() {
    Dust::Color oxygen_color = Dust::Color({1,1,.1,.1});
    Dust::Element element = Dust::Element("Oxygen", &oxygen_color, 1);
    Dust::Particle particle = Dust::Particle(0, 1, 2, element);
    particles.push_back(particle);
    Logger::log("Testing!");
    while (update()) {
        std::vector<Field> fields = physics.tick();
        for(auto val : fields){

        }
    }
    return 0;
}
