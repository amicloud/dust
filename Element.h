//
// Created by Amy on 12/31/2020.
//

#ifndef DUST_ELEMENT_H
#define DUST_ELEMENT_H
#pragma once

#include <cstdint>
#include <vector>

namespace Dust {
    static std::vector<uint32_t> ids;
    struct Color {
        float r, g, b, a;
    };

    class Element {

    private:
        const char *name{};
        const Color *color{};
        const uint32_t id;
        //and some way to do interactions idk lol
    public:
        Element() : id(0) {};
        Element(const char* name, Color* color, uint32_t id) : name("Element"), color(color), id(id) {};
    };
}


#endif //DUST_ELEMENT_H
