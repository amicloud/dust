//
// Created by Amy on 1/17/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

namespace Dust {

    Shader::Shader(const std::string &filePath) {
        source = ParseShader(filePath);
        program = CreateShader(source.VertexSource, source.FragmentSource);
    }

    Shader::ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss[2];
        ShaderType shaderType = ShaderType::NONE;
        #if SHADER_DEBUG == 1
        std::cout << filepath << std::endl;
        #endif
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    shaderType = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    shaderType = ShaderType::FRAGMENT;
                }
            } else {
                ss[(int) shaderType] << line << "\n";
                #if SHADER_DEBUG == 1
                std::cout << line.c_str() << std::endl;
                #endif
            }
        }
        return {ss[0].str(), ss[1].str()};
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
        unsigned int program = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(program, 1, &src, nullptr);
        glCompileShader(program);
        int result;
        glGetShaderiv(program, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(program, length, &length, message);
            std::cout << "SHADER FAILED TO COMPILE" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(program);
            return 0;
        }
//        std::cout << "SHADER SUCCESSFULLY COMPILED" << std::endl;
        return program;
    }

    unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        return program;
    }

    void Shader::unbind() {
        glUseProgram(0);
    }

    void Shader::bind() {
        glUseProgram(program);
    }
}