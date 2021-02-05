//
// Created by Amy on 1/26/2021.
//
#pragma once
#ifndef DUST_GUI_H
#define DUST_GUI_H

#include <physics/2d/Physics2D.h>
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
                Physics2D::stopPhysics();
                Physics2D::startPhysics();
            }
            ImGui::SliderFloat("X", &addPosX, -300.0f, 300.0f);
            ImGui::SliderFloat("Y", &addPosY, -300.0f, 300.0f);
            if(ImGui::Button("Play/Pause Physics")){
                if(Physics2D::doingPhysics){
                    Physics2D::stopPhysics();
                } else {
                    Physics2D::startPhysics();
                }
            }
            if(ImGui::Button("Delete All")){
                Physics2D::clearParticles();
            }
            if(ImGui::Button("Add UP R")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::RED});
            }
            if(ImGui::Button("Add UP G")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::GREEN});
            }
            if(ImGui::Button("Add UP B")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::UP, ColorCharge::BLUE});
            }
            if(ImGui::Button("Add DOWN R")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::RED});
            }
            if(ImGui::Button("Add DOWN G")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::GREEN});
            }
            if(ImGui::Button("Add DOWN B")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::DOWN, ColorCharge::BLUE});
            }
            if(ImGui::Button("Add UUD RGB")){
                Physics2D::stopPhysics();
                Physics2D::particlePhysics.createParticle({{addPosX + triangleOffset, addPosY}, Flavor::UP, ColorCharge::RED});
                Physics2D::particlePhysics.createParticle({{addPosX - triangleOffset, addPosY}, Flavor::UP, ColorCharge::GREEN});
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY + triangleOffset}, Flavor::DOWN, ColorCharge::BLUE});
//                Physics2D::ParticleSystem2D.createParticle({addPosX,addPosY}, Flavor::DOWN, ColorCharge::BLUE);
                Physics2D::startPhysics();
            }
            if(ImGui::Button("Add UDD RGB")){
                Physics2D::stopPhysics();
                Physics2D::particlePhysics.createParticle({{addPosX + triangleOffset, addPosY}, Flavor::UP, ColorCharge::RED});
                Physics2D::particlePhysics.createParticle({{addPosX - triangleOffset, addPosY}, Flavor::DOWN, ColorCharge::GREEN});
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY + triangleOffset}, Flavor::DOWN, ColorCharge::BLUE});
                Physics2D::startPhysics();
            }
            if(ImGui::Button("Add Electron")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::ELECTRON});
            }
            if(ImGui::Button("Add Proton")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::PROTON});
            }
            if(ImGui::Button("Add Neutron")){
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::NEUTRON});
            }
            if(ImGui::Button("Add Hydrogen Molecule")){
                Physics2D::stopPhysics();
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY}, Flavor::PROTON});
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY + (triangleOffset * 5)}, Flavor::ELECTRON});
                Physics2D::startPhysics();
            }
            if(ImGui::Button("Add Deuterium Molecule")){
                Physics2D::stopPhysics();
                Physics2D::particlePhysics.createParticle({{addPosX + triangleOffset, addPosY}, Flavor::NEUTRON});
                Physics2D::particlePhysics.createParticle({{addPosX - triangleOffset, addPosY}, Flavor::PROTON});
                Physics2D::particlePhysics.createParticle({{addPosX, addPosY + (triangleOffset * 10)}, Flavor::ELECTRON});
                Physics2D::startPhysics();
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
