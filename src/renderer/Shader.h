//
// Created by Amy on 1/17/2021.
//
#pragma once
#ifndef DUST_SHADER_H
#define DUST_SHADER_H

#include <string>

namespace Dust {


    class Shader {
        struct ShaderProgramSource {
            std::string VertexSource, FragmentSource;
        };
        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        static ShaderProgramSource ParseShader(const std::string &filepath);

        static unsigned int CompileShader(unsigned int type, const std::string &source);

        static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    public:
        explicit Shader(const std::string& filePath);
        ShaderProgramSource source;
        unsigned int program;
        void bind();
        void unbind();
    };
}

#endif //DUST_SHADER_H
