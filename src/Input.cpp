//
// Created by Amy on 1/24/2021.
//
#include <GLFW/glfw3.h>
#include "Input.h"

namespace Dust {

    void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }

    Input::Input(GLFWwindow *_window) {
        window = _window;
        glfwSetKeyCallback(window, (GLFWkeyfun)keyCallback);

    }



}