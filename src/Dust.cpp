#include <iostream>
#include <vector>
#include "Dust.h"
//#define log(x) Dust::Logging::debug(x)
#define GLEW_STATIC 1

#include "renderer/Renderer.h"
//#include "Physics.h"
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "../dependencies/catch.hpp"
//using namespace Dust;
#include "physics/Field.h"
#include "physics/SimplePhysics.h"
#include <random>

using namespace Dust;

int main() {

    Renderer renderer;

    Logger::debug("Testing!");

    SimplePhysics::startPhysics();
    while (renderer.rendering) {
        auto *timer = new Logger::Timer(false, "Render");

        renderer.draw();
        delete timer;
    }
    SimplePhysics::stopPhysics();
    return 0;
}


