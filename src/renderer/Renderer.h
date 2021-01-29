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
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Shader.h"
#include "Physics.h"
#include "SimplePhysics.h"
#include "Field.h"
#include "ParticleSystem.h"
#include "SimplePhysics.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "ui/Gui.h"
#include <gtc/type_ptr.hpp>
#define glCall(x) GLClearError(); x; ASSERT(GLLogError())

static void GLClearError(){
    while(glGetError());
}

static bool GLLogError(){
    while(GLenum error = glGetError()){
        std::cout << "[OPENGL ERROR]: " << error << std::endl;
        return false;
    }
    return true;
}

namespace Dust {


    class Renderer {

        struct TextObject {
            std::string text;
            bool draw;
            double val;
        };

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    public:
//        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) universeSizeX / (float)universeSizeY, 0.1f, 100.0f);
        glm::mat4 projectionMatrix = glm::ortho(-(float)universeSizeX/2, (float)universeSizeX/2, -(float)universeSizeY/2, (float)universeSizeY/2, 0.0f, 100.0f);
        inline static std::vector<TextObject> guiTextQueue = {};
        bool rendering = true;
        unsigned int particleBuffer;
        std::string glUserParam;
        unsigned int backgroundBuffer;
        unsigned int ibo;
        Renderer() {
            /* Initialize the glfw library */
            if (!glfwInit()) {
                std::cerr << "GLFW init failed." << std::endl;
            }
            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(universeSizeX, universeSizeY, "Dust", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                std::cerr << "GLFW window create failed." << std::endl;
            }
            /* Make the window's context current */
            glfwMakeContextCurrent(window);
            Gui::startImGui(window);
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                std::cerr << "GLEW init failed.." << std::endl;
                Logger::err(Logger::ErrorType::OPEN_GL_ERROR, err);
            }
            glfwSwapInterval(vSync);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

            std::string fieldShaderFilepath = "../res/shaders/Field.glsl";
            std::string particleShaderFilepath = "../res/shaders/Particle.glsl";
            std::string newParticleShaderFilepath = "../res/shaders/Particle2.glsl";
            std::string backgroundShaderFilepath = "../res/shaders/Background.glsl";
            fieldShader = new Shader(fieldShaderFilepath);
            particleShader = new Shader(particleShaderFilepath);
            newParticleShader = new Shader(newParticleShaderFilepath);
            backgroundShader = new Shader(backgroundShaderFilepath);



            glCall(glGenBuffers(1, &backgroundBuffer));
            glCall(glGenBuffers(1, &ibo));
            glCall(glGenBuffers(1, &particleBuffer));
            glCall(glGenBuffers(1, &ssbo));

            glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo));
            glCall(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(fieldBufferData), &fieldBufferData, GL_STREAM_COPY));
            glCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo));
            glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo));
            glEnable(GL_PROGRAM_POINT_SIZE);
            glCall(glOrtho(0.0, 500.0f, 0.0f, 700.0f, 0.0f, 100.0f));
        };

        void terminate() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void renderField() {
            fieldShader->bind();
            int xScaleLocation = glGetUniformLocation(fieldShader->program, "u_xScale");
            int yScaleLocation = glGetUniformLocation(fieldShader->program, "u_yScale");
            int maxMagLocation = glGetUniformLocation(fieldShader->program, "u_maxMag");
            glCall(glUniform1d(maxMagLocation, fieldForRender->maxMagnitude));
            glCall(glUniform1i(xScaleLocation, universeSizeX));
            glCall(glUniform1i(yScaleLocation, universeSizeY));
            glCall(glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(fieldForRender->flatPacked), &fieldForRender->flatPacked));
            glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            fieldShader->unbind();
        }

        void renderParticles() {
            particleShader->bind();
            int xScaleLocation = glGetUniformLocation(fieldShader->program, "u_xScale");
            int yScaleLocation = glGetUniformLocation(fieldShader->program, "u_yScale");
            int maxMagLocation = glGetUniformLocation(fieldShader->program, "u_maxMag");

            glCall(glUniform1i(xScaleLocation, universeSizeX));
            glCall(glUniform1i(yScaleLocation, universeSizeY));
            glCall(glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(SimplePhysics::ParticleSystem.flatPacked),
                            SimplePhysics::ParticleSystem.flatPacked));
            glCall(glBindBuffer(GL_ARRAY_BUFFER, backgroundBuffer));
            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            particleShader->unbind();
        }

        void renderParticlesNew(){
            if(SimplePhysics::ParticleSystem.forRender.empty()) return;

            newParticleShader->bind();
            glCall(glBindBuffer(GL_ARRAY_BUFFER, particleBuffer));
            glCall(glBufferData(GL_ARRAY_BUFFER, SimplePhysics::ParticleSystem.forRender.size() * sizeof(ParticleSystem::ParticleForRender), &SimplePhysics::ParticleSystem.forRender.front(), GL_DYNAMIC_DRAW));
            glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr));
            glCall(glEnableVertexAttribArray(0));

            int orthoLocation = glGetUniformLocation(backgroundShader->program, "ortho");
            glCall(glUniformMatrix4fv(orthoLocation, 1, false, glm::value_ptr(projectionMatrix)));

            glCall(glDrawArrays(GL_POINTS, 0, SimplePhysics::ParticleSystem.forRender.size()));
//            glCall(glDrawArrays(GL_TRIANGLES, 0, SimplePhysics::ParticleSystem.forRender.size()-1));

            newParticleShader->unbind();
        }

        void renderBackground() {
            backgroundShader->bind();
            glCall(glBindBuffer(GL_ARRAY_BUFFER, backgroundBuffer));
            glCall(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), rectangle, GL_STATIC_DRAW));
            glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr));
            glCall(glEnableVertexAttribArray(0));

            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            glCall(glEnableVertexAttribArray(0));

            int orthoLocation = glGetUniformLocation(backgroundShader->program, "ortho");
            glCall(glUniformMatrix4fv(orthoLocation, 1, false, glm::value_ptr(projectionMatrix)));

            glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//            glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
//            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            backgroundShader->unbind();
            glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
            glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        int draw() {
            auto *timer = new Logger::Timer(false, "Frame draw");
            if (!glfwWindowShouldClose(window)) {
                glCall(glClear(GL_COLOR_BUFFER_BIT));

                renderBackground();
//                renderParticles();
                renderParticlesNew();
//                renderField();

                Gui::renderGui();

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            } else {
//                glDeleteProgram();
//                glCall(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));
                terminate();
                rendering = false;
                return 0;
            }
            delete timer;
            return 1;
        }

        void submitField(Field &field) {
            fieldForRender = &field;
        }

    private:
        GLFWwindow *window;
        Shader *fieldShader;
        Shader *particleShader;
        Shader *backgroundShader;
        Shader *newParticleShader;
        Field *fieldForRender{};
        std::vector<Vec2<float>> pointsForRender;
        float rectangle[8] = {-(float)universeSizeX/2, -(float)universeSizeY/2, (float)universeSizeX/2, -(float)universeSizeY/2,
                              (float)universeSizeX/2, (float)universeSizeY/2,  -(float)universeSizeX/2, (float)universeSizeY/2};
//        float rectangle[8] = {-300, -300, 300, -300,
//                              300, 300,  -300, 300};
        unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
        double fieldBufferData[universeSizeX * universeSizeY]{};
        GLuint ssbo{};
        GLvoid *p{};
        bool vSync = true;
//        -(float)universeSizeX/2, (float)universeSizeX/2, -(float)universeSizeY/2, (float)universeSizeY/2
    };
}


#endif //DUST_RENDERER_H
