//
// Created by Amy on 1/24/2021.
//

#include <GLFW/glfw3.h>
#ifndef DUST_INPUT_H
#define DUST_INPUT_H

namespace Dust {

    class Input {

        bool mouseLeftDown = false;
        bool mouseRightDown = false;
        bool mouseMiddleDown = false;
        GLFWwindow* window;
        explicit Input(GLFWwindow* _window);


        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
}

#endif //DUST_INPUT_H
