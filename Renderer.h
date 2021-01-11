//
// Created by Amy on 12/31/2020.
//

//#include <GLFW/glfw3.h>

//#include <GLFW/glfw3.h>

#define GLEW_STATIC 1

#ifndef DUST_RENDERER_H
#define DUST_RENDERER_H
#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"

#include <vector>
#include <iostream>
#include "Particle.h"
#include "Constants.h"

namespace Dust {
    class Renderer {
    private:
        GLFWwindow *window;
    public:

        Renderer(){
            /* Initialize the glfw library */
            if (!glfwInit()) {
                std::cerr << "GLFW init failed." << std::endl;
            }
            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(universeSize, universeSize, "Dust", NULL, NULL);
            if (!window) {
                glfwTerminate();
                std::cerr << "GLFW window create failed." << std::endl;
            }
            /* Make the window's context current */
            glfwMakeContextCurrent(window);
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                std::cerr << "GLEW init failed.." << std::endl;
                Logger::err(err);
            }
        };


        template<typename T>
        int render(T data) {


            return 0;
        }

        void terminate(){
            glfwTerminate();
        }

        int draw() {
            if (!glfwWindowShouldClose(window)) {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
                glBegin(GL_TRIANGLES);
                glVertex2f(-.05f, -0.5f);
                glVertex2f(0.0f, 0.5f);
                glVertex2f(0.5f, -0.5f);

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            } else {
                terminate();
                return 0;
            }

            return 1;
        }
    };
}


#endif //DUST_RENDERER_H
