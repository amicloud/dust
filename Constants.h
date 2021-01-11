//
// Created by Amy on 1/10/2021.
//

#pragma once


const uint32_t universeSize = 10;

struct Vec4 {
    uint16_t x = 0, y = 0;
    float magnitude = 0, d = 0;
};

struct Position {
    uint32_t x, y;
};

struct Color3 {
    float r, g, b;
};

struct Color4 {
    float a,r,g,b;
};

struct Renderable {
    Color4 color;

};
