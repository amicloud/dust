#include <iostream>
#include <vector>
#include "Dust.h"
//#define log(x) Dust::Logging::debug(x)
#define GLEW_STATIC 1

#include "renderer/Renderer.h"

using namespace Dust;

int main() {

    Renderer renderer;

    Logger::debug("Testing!");

    Physics2D::startPhysics();
    while (renderer.rendering) {
        auto *timer = new Logger::Timer(false, "Render");

        renderer.draw();
        delete timer;
    }
    Physics2D::stopPhysics();
    return 0;
}


