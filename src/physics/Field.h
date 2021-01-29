//
// Created by Amy on 1/18/2021.
//
#pragma once
#ifndef DUST_FIELD_H
#define DUST_FIELD_H
#define FIELD_DEBUG

//typedef Vec4 Vec2;

#include <iostream>
//#include "Physics.h"
#include "../Logger.h"
#include <iterator>
#include "../Constants.h"
#include <vector>
class Field {

    struct WorldLine {
        double points[universeSizeX];
    };

public:
//    static std::vector<void*> _fields;
    WorldLine lines[universeSizeY]{};
    WorldLine tempLines[universeSizeY]{};

    double flatPacked[universeSizeY * universeSizeX]{};
    double maxMagnitude = std::numeric_limits<double>::min();
    double minMagnitude = std::numeric_limits<double>::max();
    double vacuumEnergy;
    double scalars[universeSizeY][universeSizeX]{};
    double tempScalars[universeSizeY][universeSizeX]{};
    double (*currentScalarsArray)[universeSizeX] = scalars;
    double (*currentTempScalarsArray)[universeSizeX] = tempScalars;
    double ninth = 1.0 / 9.0;
    double v3;
    double v5;
    double permeability;
    double propagationRate;
    template<typename T>
    void addMagnitude(T magnitude, Vec2<double> position) {
        lines[(int) position.y].points[(int) position.x] += magnitude;
        scalars[(int) position.y][(int) position.x] += magnitude;
    }

    explicit Field(double _vacuumEnergy, double _permeability) {
        vacuumEnergy = _vacuumEnergy;
        int flatIndex = 0;
        for (uint32_t i = 0; i < universeSizeY; i++) {
            for (uint32_t j = 0; j < universeSizeX; j++) {
                lines[i].points[j] = vacuumEnergy;
                tempLines[i].points[j] = vacuumEnergy;
                scalars[i][j] = vacuumEnergy;
                tempScalars[i][j] = vacuumEnergy;
                flatPacked[flatIndex] = vacuumEnergy;
                flatIndex++;
                v3 = (vacuumEnergy * (float) 3);
                v5 = (vacuumEnergy * (float) 5);
                permeability = _permeability;
                propagationRate = permeability * ninth;
            }
        }
        Logger::debug("Field created.");
//        _fields.push_back(this);
    }

//    ~Field(){
//        _fields.erase(std::find(_fields.begin(), _fields.end(), this));
//        Logger::info("Field deleted.");
//    }

    void propagateMagnitudesNew() {

        maxMagnitude = std::numeric_limits<double>::min();
        minMagnitude = std::numeric_limits<double>::max();
        int flatIndex = 0;
        for (uint32_t i = 0; i < universeSizeY; i++) {
            for (uint32_t j = 0; j < universeSizeX; j++) {
                tempLines[i].points[j] = 0;
                int edges = 8;
                if (i != 0) {
                    if (j != universeSizeX - 1) {
                        //q3
                        tempLines[i].points[j] += lines[i - 1].points[
                                j + 1];
                        edges--;
                    }

                    //q1
                    if (j != 0) {
                        tempLines[i].points[j] += lines[i - 1].points[
                                j - 1];
                        edges--;
                    }
                    //q2
                    tempLines[i].points[j] += lines[i - 1].points[
                            j];
                    edges--;
                }

                //q4
                if (j != 0) {
                    tempLines[i].points[j] += lines[i].points[
                            j - 1];
                    edges--;
                }

                //q5
                tempLines[i].points[j] += lines[i].points[
                        j];

                //q6
                if (j != universeSizeX - 1) {
                    tempLines[i].points[j] += lines[i].points[
                            j + 1];
                    edges--;
                }


                if (i != universeSizeY - 1) {
                    //q7
                    if (j != 0) {
                        tempLines[i].points[j] += lines[i + 1].points[
                                j - 1];
                        edges--;
                    }
                    //q8
                    tempLines[i].points[j] += lines[i + 1].points[
                            j];
                    edges--;
                }

                //q9
                if (i != universeSizeY - 1) {
                    if (j != universeSizeX - 1) {
                        tempLines[i].points[j] += lines[i + 1].points[
                                j + 1];
                        edges--;
                    }
                }

                tempLines[i].points[j] += (vacuumEnergy * (float) edges);
                if (tempLines[i].points[j] == std::numeric_limits<double>::max()) {
                    Logger::err(Logger::ErrorType::PHYSICS_ERROR, "Infinity in field.");
                    tempLines[i].points[j] = std::numeric_limits<double>::max();
                }
                tempLines[i].points[j] *= ninth;
                flatPacked[flatIndex] = tempLines[i].points[j];
                flatIndex++;
                if (tempLines[i].points[j] > maxMagnitude) {
                    maxMagnitude = tempLines[i].points[j];

                }
                if (tempLines[i].points[j] < minMagnitude) {
                    minMagnitude = tempLines[i].points[j];

                }
            }
            memcpy(lines + i, tempLines + i, sizeof(double) * (universeSizeX));
        }

    }

    void propagateWithRolling() {

    }

    void propagateMagnitudesOptimizedScalarsMatrix() {
        maxMagnitude = std::numeric_limits<double>::min();
//        if(currentScalarsArray == scalars){
//            currentScalarsArray = &tempScalars[0];
//            currentTempScalarsArray = &scalars[0];
//
//        } else {
//            currentScalarsArray = &scalars[0];
//            currentTempScalarsArray = &tempScalars[0];
//        }

//        //corners
//        //top left
//        tempScalars[0][0] = v5;
//        tempScalars[0][0] += scalars[0][0] +
//                             scalars[1][0] +
//                             scalars[0][1] +
//                             scalars[1][1];
//        tempScalars[0][0] *= propagationRate;
//
//        //top right
//        tempScalars[0][universeSizeX - 1] = v5;
//        tempScalars[0][universeSizeX - 1] += scalars[0][universeSizeX - 1] +
//                                             scalars[0][universeSizeX - 1 - 1] +
//                                             scalars[1][universeSizeX - 1] +
//                                             scalars[1][universeSizeX - 1 - 1];
//        tempScalars[0][universeSizeX - 1] *= propagationRate;
//
//        //bottom left
//        tempScalars[universeSizeY - 1][0] = v5;
//        tempScalars[universeSizeY - 1][0] += scalars[universeSizeY - 1][0] +
//                                             scalars[universeSizeY - 1 - 1][0] +
//                                             scalars[universeSizeY - 1][1] +
//                                             scalars[universeSizeY - 1 - 1][1];
//        tempScalars[universeSizeY - 1][0] *= propagationRate;
//
//        //bottom right
//        tempScalars[universeSizeY - 1][universeSizeX - 1] = v5;
//        tempScalars[universeSizeY - 1][universeSizeX - 1] += scalars[universeSizeY - 1][universeSizeX - 1] +
//                                                             scalars[universeSizeY - 1 - 1][universeSizeX - 1] +
//                                                             scalars[universeSizeY - 1][universeSizeX - 1 - 1] +
//                                                             scalars[universeSizeY - 1][universeSizeX - 1 - 1];
//        tempScalars[universeSizeY - 1][universeSizeX - 1] *= propagationRate;
//
//        //top and bottom
//        for (int j = 1; j < universeSizeX - 1; j++) {
//            //top
//            tempScalars[0][j] = v3;
//            tempScalars[0][j] += scalars[0][j] +
//                                 scalars[0][j - 1] +
//                                 scalars[0][j + 1] +
//                                 scalars[1][j] +
//                                 scalars[1][j - 1] +
//                                 scalars[1][j + 1];
//            tempScalars[0][j] *= propagationRate;
//            flatPacked[j] = tempScalars[0][j];
//            if (tempScalars[0][j] > maxMagnitude) maxMagnitude = tempScalars[0][j];
//
//
//            //bottom
//            tempScalars[universeSizeY - 1][j] = v3;
//            tempScalars[universeSizeY - 1][j] += scalars[universeSizeY - 1][j] +
//                                                 scalars[universeSizeY - 1][j - 1] +
//                                                 scalars[universeSizeY - 1][j + 1] +
//                                                 scalars[universeSizeY - 2][j] +
//                                                 scalars[universeSizeY - 2][j - 1] +
//                                                 scalars[universeSizeY - 2][j + 1];
//            tempScalars[universeSizeY - 1][j] *= propagationRate;
//            flatPacked[(universeSizeY - 1 * universeSizeX) + j] = tempScalars[universeSizeY - 1][j];
//            if (tempScalars[universeSizeY - 1][j] > maxMagnitude) maxMagnitude = tempScalars[universeSizeY - 1][j];
//        }
//        //sides
//        for (int i = 1; i < universeSizeY - 1; i++) {
//            //left
//            tempScalars[i][0] = v3;
//            tempScalars[i][0] += scalars[i][0];
//            tempScalars[i][0] += scalars[i + 1][0];
//            tempScalars[i][0] += scalars[i - 1][0];
//            tempScalars[i][0] += scalars[i][1];
//            tempScalars[i][0] += scalars[i + 1][1];
//            tempScalars[i][0] += scalars[i - 1][1];
//            tempScalars[i][0] *= propagationRate;
//            flatPacked[i * universeSizeX] = tempScalars[i][0];
//            if (tempScalars[i][0] > maxMagnitude) maxMagnitude = tempScalars[i][0];
//            //right
//            tempScalars[i][universeSizeX - 1] = v3;
//            tempScalars[i][universeSizeX - 1] += scalars[i][universeSizeX - 1];
//            tempScalars[i][universeSizeX - 1] += scalars[i + 1][universeSizeX - 1];
//            tempScalars[i][universeSizeX - 1] += scalars[i - 1][universeSizeX - 1];
//            tempScalars[i][universeSizeX - 1] += scalars[i][universeSizeX - 2];
//            tempScalars[i][universeSizeX - 1] += scalars[i + 1][universeSizeX - 2];
//            tempScalars[i][universeSizeX - 1] += scalars[i - 1][universeSizeX - 2];
//            tempScalars[i][universeSizeX - 1] *= propagationRate;
//            flatPacked[i * universeSizeX + universeSizeX - 1] = tempScalars[i][universeSizeX - 1];
//            if (tempScalars[i][universeSizeX - 1] > maxMagnitude) maxMagnitude = tempScalars[i][universeSizeX - 1];
//        }
        //interior
//        for (int i = 1; i < universeSizeY - 1; i++) {
//            for (int j = 1; j < universeSizeX - 1; j++) {
//                tempScalars[i][j] = 0;
//                tempScalars[i][j] += scalars[i + 1][j - 1];
//                tempScalars[i][j] += scalars[i + 1][j];
//                tempScalars[i][j] += scalars[i + 1][j + 1];
//                tempScalars[i][j] += scalars[i - 1][j - 1];
//                tempScalars[i][j] += scalars[i - 1][j];
//                tempScalars[i][j] += scalars[i - 1][j + 1];
//                tempScalars[i][j] += scalars[i][j - 1];
//                tempScalars[i][j] += scalars[i][j];
//                tempScalars[i][j] += scalars[i][j + 1];
//                tempScalars[i][j] *= propagationRate;
//                flatPacked[i * universeSizeX + j] = tempScalars[i][j];
//                if (tempScalars[i][j] > maxMagnitude) maxMagnitude = tempScalars[i][j];
//            }
//        }
        //interior
        for (int i = 1; i < universeSizeY - 1; i++) {
            for (int j = 1; j < universeSizeX - 1; j++) {
                currentTempScalarsArray[i][j] = 0;
                currentTempScalarsArray[i][j] += currentScalarsArray[i + 1][j - 1];
                currentTempScalarsArray[i][j] += currentScalarsArray[i + 1][j];
                currentTempScalarsArray[i][j] += currentScalarsArray[i + 1][j + 1];
                currentTempScalarsArray[i][j] += currentScalarsArray[i - 1][j - 1];
                currentTempScalarsArray[i][j] += currentScalarsArray[i - 1][j];
                currentTempScalarsArray[i][j] += currentScalarsArray[i - 1][j + 1];
                currentTempScalarsArray[i][j] += currentScalarsArray[i][j - 1];
                currentTempScalarsArray[i][j] += currentScalarsArray[i][j];
                currentTempScalarsArray[i][j] += currentScalarsArray[i][j + 1];
                currentTempScalarsArray[i][j] *= propagationRate;
                flatPacked[i * universeSizeX + j] = currentTempScalarsArray[i][j];
                if (tempScalars[i][j] > maxMagnitude) maxMagnitude = currentTempScalarsArray[i][j];
            }
        }
//        Logger::debug(maxMagnitude, "Max Magnitude");
        memcpy(scalars, tempScalars, sizeof(double) * (universeSizeX * universeSizeY));

//        if(currentScalarsArray == scalars){
//            currentScalarsArray = tempScalars;
//            currentTempScalarsArray = scalars;
//
//        } else {
//            currentScalarsArray = scalars;
//            currentTempScalarsArray = tempScalars;
//        }

    }




    void print() {

        #ifdef FIELD_DEBUG
        for (WorldLine line : lines) {
            for (float vec : line.points) {
                std::cout << vec << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        #endif
    }

    void setupForTesting() {

    }

    Vec2<double> getVectorAtPosition(Vec2<double> position) {
        int posX = (int) position.x;
        int posY = (int) position.y;
        if (position.x == 0 || position.y == 0 || position.x == universeSizeX || position.y == universeSizeY)
            return {0, 0};
        Vec2<double> res = {scalars[posY][posX+1]/scalars[posY][posX] - scalars[posY][posX-1]/scalars[posY][posX],
                            scalars[posY+1][posX]/scalars[posY][posX] - scalars[posY-1][posX]/scalars[posY][posX]};
        return res;
    }

    void propagate() {
        auto *timer = new Logger::Timer(false, "Field propagation.");
//        propagateMagnitudesNew();
//        propagateMagnitudesOptimized();
        propagateMagnitudesOptimizedScalarsMatrix();
        delete timer;
    }


};

#include <chrono>
#include "../Constants.h"
#include "../../dependencies/catch.hpp"

#endif //DUST_FIELD_H
