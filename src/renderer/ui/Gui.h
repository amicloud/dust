//
// Created by Amy on 1/26/2021.
//
#pragma once
#ifndef DUST_GUI_H
#define DUST_GUI_H

#include <SimplePhysics.h>
//#include "Constants.h"

namespace Dust {
    class Gui {

    public:
        Gui();


        static void startImGui(GLFWwindow* window) {
            const char *glsl_version = "#version 430";
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void) io;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init(glsl_version);
        }


        inline static float addPosX = 0, addPosY = 0;
        inline static float triangleOffset = 2;
        static void renderGui() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin(
                    "Control Center");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat("Gravity", &gravityModifier, 0.000f, 100.0f);
            ImGui::SliderFloat("Electric force", &fineStructureConstant, 0.000f, 01.0f);
            ImGui::SliderFloat("Strong interaction", &strongInteraction, -2.000f, 2.0f);
            ImGui::SliderFloat("Weak interaction", &weakInteraction, 0.000f, 0.1f);
            if(ImGui::SliderInt("Physics Time Step", &physicsTimeStep, 1, 1000)){
                SimplePhysics::stopPhysics();
                SimplePhysics::startPhysics();
            }
            ImGui::SliderFloat("X", &addPosX, -300.0f, 300.0f);
            ImGui::SliderFloat("Y", &addPosY, -300.0f, 300.0f);
            if(ImGui::Button("Play/Pause Physics")){
                if(SimplePhysics::doingPhysics){
                    SimplePhysics::stopPhysics();
                } else {
                    SimplePhysics::startPhysics();
                }
            }
            if(ImGui::Button("Delete All")){
                SimplePhysics::ParticleSystem.clearAll();
            }
            if(ImGui::Button("Add UP R")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::RED});
            }
            if(ImGui::Button("Add UP G")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::GREEN});
            }
            if(ImGui::Button("Add UP B")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::BLUE});
            }
            if(ImGui::Button("Add DOWN R")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::RED});
            }
            if(ImGui::Button("Add DOWN G")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::GREEN});
            }
            if(ImGui::Button("Add DOWN B")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::BLUE});
            }
            if(ImGui::Button("Add UUD RGB")){
                SimplePhysics::stopPhysics();
                SimplePhysics::ParticleSystem.createParticle({{addPosX + triangleOffset, addPosY}, Flavor::UP, ColorCharge::RED});
                SimplePhysics::ParticleSystem.createParticle({{addPosX - triangleOffset, addPosY}, Flavor::UP, ColorCharge::GREEN});
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY + triangleOffset}, Flavor::DOWN, ColorCharge::BLUE});
//                SimplePhysics::ParticleSystem.createParticle({addPosX,addPosY}, Flavor::DOWN, ColorCharge::BLUE);
                SimplePhysics::startPhysics();
            }
            if(ImGui::Button("Add UDD RGB")){
                SimplePhysics::stopPhysics();
                SimplePhysics::ParticleSystem.createParticle({{addPosX + triangleOffset, addPosY}, Flavor::UP, ColorCharge::RED});
                SimplePhysics::ParticleSystem.createParticle({{addPosX - triangleOffset, addPosY}, Flavor::DOWN, ColorCharge::GREEN});
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY + triangleOffset}, Flavor::DOWN, ColorCharge::BLUE});
                SimplePhysics::startPhysics();
            }
            if(ImGui::Button("Add Electron")){
                SimplePhysics::ParticleSystem.createParticle({{addPosX, addPosY}, Flavor::ELECTRON});
            }
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            ImGui::Text("-Information Center-");


            ImGui::End();

            ImGui::Render();
//            int display_w, display_h;
//            glfwGetFramebufferSize(window, &display_w, &display_h);
//            glViewport(0, 0, display_w, display_h);
//            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
//            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }

    private:
    };
}

#endif //DUST_GUI_H
