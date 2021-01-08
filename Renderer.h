//
// Created by Amy on 12/31/2020.
//

//#include <GLFW/glfw3.h>

//#include <GLFW/glfw3.h>

#define GLEW_STATIC 1

#ifndef DUST_RENDERER_H
#define DUST_RENDERER_H
#pragma once


namespace Dust {
    class Renderer {
    private:
        uint16_t view_x, view_y;
        const char *window_title;
        std::vector<Particle>* particles;
//        GLFWwindow *window;
    public:
        Renderer();
        Renderer(uint16_t x, uint16_t y, const char* win_title, std::vector<Particle>* particles);
        int render();
        void terminate();
        int draw();
    };
}


#endif //DUST_RENDERER_H
