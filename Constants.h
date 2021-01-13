//
// Created by Amy on 1/10/2021.
//

#pragma once


const uint32_t universeSize = 100;

struct Vec4 {
    uint16_t x = 0, y = 0;
    float magnitude = 0, d = 0;
};

struct Position {
    uint32_t x, y;
};

struct Color {
    float a = 0,r = 0,g = 0,b = 0;
};


struct Renderable {
    Color color;
    Position position{};
};

Color magnitudeToColor(float mag, float maxMag){
    Color color;
    float third = maxMag/3;
    float ratio = mag/maxMag;
    if(mag < third){
        color.r = ratio;
    } else if( mag < third*2) {
        color.r = 1;
        color.g = ratio;
    } else {
        color.r = 1;
        color.g = 1;
        color.b = ratio;
    }
    return color;
}


Renderable vec4ToRenderable(Vec4 vec, float maxMag){
    Color color = magnitudeToColor(vec.magnitude, maxMag);
    auto position = Position{vec.x, vec.y};
    return {color, position};
}