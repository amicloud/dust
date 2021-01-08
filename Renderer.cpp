//
// Created by Amy on 12/31/2020.
//
//
// Created by Amy on 12/31/2020.
//


#ifndef DUST_RENDERER_H
#define DUST_RENDERER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"

#include <vector>
#include <iostream>
#include "Particle.h"

namespace Dust {
    class Renderer {
    private:
        uint16_t view_x, view_y;
        const char *window_title;
        std::vector<Particle>* particles;
        GLFWwindow *window;
    public:
        Renderer() = default;
         Renderer(uint16_t x, uint16_t y, const char* win_title, std::vector<Particle>* particles) : view_x(x), view_y(y), window_title(win_title), particles(particles) {
            /* Initialize the glfw library */
            if (!glfwInit()) {
                std::cerr << "GLFW init failed." << std::endl;
            }
            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(view_x, view_y, window_title, NULL, NULL);
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

        int render() {
            std::vector<float> vertices;
            for (auto particle : *particles) {

            }
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

#endif
//#include "Renderer.h"
