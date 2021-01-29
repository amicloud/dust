//
// Created by Amy on 1/10/2021.
//

#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <algorithm>

#define ASSERT(x) if(!(x)) __debugbreak()


static inline const int universeSizeX = 1200;
static inline const int universeSizeY = 700;
static inline float strongInteraction = 1.0;
static inline float weakInteraction = 1.0e-7;
static inline float fineStructureConstant = 1.0e-2;
static inline float gravityModifier = 1.0;
static inline float gravitationalConstant = 6.674e-39;
//static inline float gravitationalConstant = 6.674e-11;
static inline const double speedOfLight = 3e6;
static inline const double speedOfLightSquared = pow(speedOfLight,2);
static inline const double nucleonMass = 10000;
static inline const double electronMass = nucleonMass * (5.4462e-4);
static inline double massUnit = 1.0e3;
static inline const int dimensions = 3;
static inline int physicsTimeStep = 100;

struct Vec4 {
    uint16_t x = 0, y = 0;
    double magnitude = 0, d = 0;
};

template<typename T>
struct Vec2 {
    T x, y;

    Vec2<T>& operator=(double _other){
        x = _other;
        y = _other;
        return *this;
    }

    Vec2<T>& operator=(const Vec2<T> &_other) {
        x = _other.x;
        y = _other.y;
        return *this;
    }

    Vec2<T> operator*(const T &_other) {
        return {x * _other, y * _other};
    }

    Vec2<T> operator*(const Vec2<T> &_other) {
        return {x * _other.x, y * _other.y};
    }

    Vec2<T> operator-(const Vec2<T> &_other) {
        return {x - _other.x, y - _other.y};
    }

    Vec2<T> operator-(const T &_other) {
        return {x - _other, y - _other};
    }

    Vec2<T> operator+(const Vec2<T> &_other) {
        return {x + _other.x, y + _other.y};
    }

    Vec2<T> operator+(const T &_other) {
        return {x + _other, y + _other};
    }

    bool operator>(T _comparison){
        return (abs(x)+abs(y)) > _comparison;
    }

    bool operator<(T _comparison){
        return (abs(x)+abs(y)) < _comparison;
    }

    template <typename J>
    bool operator==(J _other){
        if((x == _other) && (y == _other)){
            return true;
        } else {
            return false;
        }
    }

    bool operator==(Vec2<T> _other){
        if((x == _other.x) && (y == _other.y)){
            return true;
        } else {
            return false;
        }
    }



    template<typename J>
    void normalize(J _xScale, J _yScale) {
        x /= (T) _xScale;
        y /= (T) _yScale;
    }

    void normalize() {
        x /= universeSizeX;
        y /= universeSizeY;
    }

    template<typename J>
    //short for jype of course
    Vec2<T> getNormalized(J _xScale, J _yScale) {
        return {x / (T) _xScale, y / (T) _yScale};
    }

    Vec2<T> getNormalized() {
        return {x / universeSizeX, y / universeSizeY};
    }

    void print() {
        std::cout << "(" << x << "," << y << ")";
    }
    void println() {
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }

    template<typename J>
    Vec2<J> cast(){
        return {(J) x, (J) y};
    }
};


struct Position {
    uint32_t x, y;
};

struct Color {
    float r = 0, g = 0, b = 0, a = 0;
};

template<typename T>
struct Renderable {
    Vec2<T> position{};
    Color color;
};



enum class Charge {
    POSITIVE = 1, NEUTRAL = 0, NEGATIVE = -1
};
//

enum class ColorCharge {
    BLACK = 0, RED = 1, ANTI_RED = -1, GREEN = 2, ANTI_GREEN = -2, BLUE = 3, ANTI_BLUE = -3

};

enum class Flavor{
    TOP = 1, BOTTOM = 2, STRANGE = 3, CHARM = 4, UP = 5, DOWN = 6,
    ELECTRON = 7, MUON = 8, TAU = 9, ELECTRON_NEUTRINO = 10, MUON_NEUTRINO = 11, TAU_NEUTRINO = 12
};

class Spin{
public:
    static inline const double HALF = 0.5;
};
class ElectricCharge {
public:
    static inline const double TWO_THIRDS= 2.0/3.0;
    static inline const double NEGATIVE_ONE_THIRD = -1.0/3.0;
    static inline const double ONE = 1.0;
    static inline const double NEGATIVE_ONE = -1.0;
    static inline const double ZERO = 0.0;
};

inline ColorCharge operator*(ColorCharge l, ColorCharge r) {
    if (l == r) {
        return ColorCharge::BLACK;
    } else {
        return (ColorCharge) std::clamp(((int) l) * ((int) r), -1, 1);
    }
}
template<typename T>
inline ColorCharge operator*(ColorCharge l, T r) {
    return ColorCharge((int)((int)l * r));
}


#endif