//
// Created by Amy on 12/31/2020.
//

#ifndef DUST_PHYSICS_H
#define DUST_PHYSICS_H
#define DEBUG
#include "Constants.h"
#include "catch.hpp"
#include <chrono>



struct WorldLine {
    Vec4 vectors[universeSize];
};

class Field {
public:
    WorldLine lines[universeSize];
    float maxMagnitude = 0, minMagnitude = 0;
    Field() = default;

    void propagateMagnitudes() {
        Field tempField;
        int m_uni_size = std::size(lines);
        int hmm = sizeof(*this);
        for (uint32_t i = 0; i < m_uni_size; i++) {
            for (uint32_t j = 0; j < m_uni_size; j++) {
                //q1
                if (i == 0) {
                    if (j == 0) {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                m_uni_size - 1].vectors[m_uni_size - 1].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                m_uni_size - 1].vectors[j - 1].magnitude;
                    }
                } else {
                    if (j == 0) {
                        tempField.lines[i].vectors[j].magnitude += lines[i - 1].vectors[
                                m_uni_size - 1].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[i - 1].vectors[
                                j - 1].magnitude;
                    }
                }

                //q2
                if (i == 0) {
                    tempField.lines[i].vectors[j].magnitude += lines[
                            m_uni_size - 1].vectors[j].magnitude;
                } else {
                    tempField.lines[i].vectors[j].magnitude += lines[i - 1].vectors[
                            j].magnitude;
                }

                //q3
                if (i == 0) {
                    if (j == m_uni_size - 1) {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                m_uni_size - 1].vectors[0].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                m_uni_size - 1].vectors[j + 1].magnitude;
                    }
                } else {
                    if (j == m_uni_size - 1) {
                        tempField.lines[i].vectors[j].magnitude += lines[i - 1].vectors[
                                0].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[i - 1].vectors[
                                j + 1].magnitude;
                    }
                }

                //q4
                if (j == 0) {
                    tempField.lines[i].vectors[j].magnitude += lines[i].vectors[
                            m_uni_size - 1].magnitude;
                } else {
                    tempField.lines[i].vectors[j].magnitude += lines[i].vectors[
                            j - 1].magnitude;
                }

                //q5
                tempField.lines[i].vectors[j].magnitude += lines[i].vectors[
                        j].magnitude;

                //q6
                if (j == m_uni_size - 1) {
                    tempField.lines[i].vectors[j].magnitude += lines[i].vectors[
                            0].magnitude;
                } else {
                    tempField.lines[i].vectors[j].magnitude += lines[i].vectors[
                            j + 1].magnitude;
                }

                //q7
                if (i == m_uni_size - 1) {
                    if (j == 0) {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                0].vectors[m_uni_size - 1].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                0].vectors[j - 1].magnitude;
                    }
                } else {
                    if (j == 0) {
                        tempField.lines[i].vectors[j].magnitude += lines[i + 1].vectors[
                                m_uni_size - 1].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[i + 1].vectors[
                                j - 1].magnitude;
                    }
                }

                //q8
                if (i == m_uni_size - 1) {
                    tempField.lines[i].vectors[j].magnitude += lines[0].vectors[j].magnitude;
                } else {
                    tempField.lines[i].vectors[j].magnitude += lines[i + 1].vectors[
                            j].magnitude;
                }

                //q9
                if (i == m_uni_size - 1) {
                    if (j == m_uni_size - 1) {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                0].vectors[0].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[
                                0].vectors[j + 1].magnitude;
                    }
                } else {
                    if (j == m_uni_size - 1) {
                        tempField.lines[i].vectors[j].magnitude += lines[i + 1].vectors[
                                0].magnitude;
                    } else {
                        tempField.lines[i].vectors[j].magnitude += lines[i + 1].vectors[
                                j + 1].magnitude;
                    }
                }
            }
        }
        for (int i = 0; i < m_uni_size; i++) {
            for (int j = 0; j < m_uni_size; j++) {
                float tempMag = tempField.lines[i].vectors[j].magnitude / 9;
                lines[i].vectors[j].magnitude = tempMag;
                if(tempMag > maxMagnitude) maxMagnitude = tempMag;
                if(tempMag < minMagnitude) minMagnitude = tempMag;
            }
        }
//        delete tempField;
    }

    void propagateMagnitudesWithRolling() {

    }

    ~Field() {
//        for(auto line : lines){
//            for(auto vec : line->vectors){
//                delete vec;
//            }
//            delete line;
//        }
//        delete this;
    }


    void print() {

#ifdef DEBUG
        for (WorldLine line : lines) {
            for (Vec4 vec : line.vectors) {
                std::cout << "(" << vec.x << "," << vec.y << "," << vec.magnitude << "," << vec.d << ")";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
#endif
    }
};


namespace Dust {

    class Physics {
        Field gravity{};


    public:
        Physics() {
            initGravity();
        }

        std::vector<Field> tick() {
            using namespace std::chrono;
            gravity.print();
            auto start = std::chrono::high_resolution_clock::now();
            gravity.propagateMagnitudes();
            gravity.print();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);

// To get the value of duration use the count()
// member function on the duration object
            std::cout << duration.count() << std::endl;
            return {gravity};
        }

    private:

        void initGravity() {
//            for (uint32_t x = 0; x < universeSize; x++) {
//                for (uint32_t y = 0; y < universeSize; y++) {
//                    gravity.lines[x)->vectors.push_back(new Vec4{x, y, 0, 0});
//                }
//            }
            gravity.lines[5].vectors[5].magnitude = 5000;
            gravity.lines[2].vectors[2].magnitude = 5000;
            gravity.lines[9].vectors[9].magnitude = 5000;
        }

    };
}

//TEST_CASE();

#endif //DUST_PHYSICS_H
