//
// Created by Amy on 12/31/2020.
//

#ifndef DUST_PHYSICS_H
#define DUST_PHYSICS_H
#define DEBUG

#include "catch.hpp"
#include <chrono>
struct Vec4 {
    uint32_t x, y;
    float magnitude, d;
};

struct WorldLine {
    std::vector<Vec4 *> vectors;
};

class Field {
public:
    std::vector<WorldLine *> lines;

    Field() = default;

    Field(Field &field) {
        memcpy(&lines, field.lines, sizeof field)
        lines = field.lines;
    };

    void propagateMagnitudes(){
        auto tempField = new Field();
        int m_uni_size = lines.size();

        for (uint32_t i = 0; i < m_uni_size; i++) {
            tempField->lines.push_back(new WorldLine{});
            for (uint32_t j = 0; j < m_uni_size; j++) {
                tempField->lines.at(i)->vectors.push_back(new Vec4{i, j, 0, 0});
                //q1
                if (i == 0) {
                    if (j == 0) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                m_uni_size - 1)->vectors.at(m_uni_size - 1)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                m_uni_size - 1)->vectors.at(j - 1)->magnitude;
                    }
                } else {
                    if (j == 0) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i - 1)->vectors.at(
                                m_uni_size - 1)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i - 1)->vectors.at(
                                j - 1)->magnitude;
                    }
                }

                //q2
                if (i == 0) {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                            m_uni_size - 1)->vectors.at(j)->magnitude;
                } else {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i - 1)->vectors.at(
                            j)->magnitude;
                }

                //q3
                if (i == 0) {
                    if (j == m_uni_size - 1) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                m_uni_size - 1)->vectors.at(0)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                m_uni_size - 1)->vectors.at(j + 1)->magnitude;
                    }
                } else {
                    if (j == m_uni_size - 1) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i - 1)->vectors.at(
                                0)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i - 1)->vectors.at(
                                j + 1)->magnitude;
                    }
                }

                //q4
                if (j == 0) {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i)->vectors.at(
                            m_uni_size - 1)->magnitude;
                } else {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i)->vectors.at(
                            j - 1)->magnitude;
                }

                //q5
                tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i)->vectors.at(
                        j)->magnitude;

                //q6
                if (j == m_uni_size - 1) {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i)->vectors.at(
                            0)->magnitude;
                } else {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i)->vectors.at(
                            j + 1)->magnitude;
                }

                //q7
                if (i == m_uni_size - 1) {
                    if (j == 0) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                0)->vectors.at(m_uni_size - 1)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                0)->vectors.at(j - 1)->magnitude;
                    }
                } else {
                    if (j == 0) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i + 1)->vectors.at(
                                m_uni_size - 1)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i + 1)->vectors.at(
                                j - 1)->magnitude;
                    }
                }

                //q8
                if (i == m_uni_size - 1) {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                            0)->vectors.at(j)->magnitude;
                } else {
                    tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i + 1)->vectors.at(
                            j)->magnitude;
                }

                //q9
                if (i == m_uni_size - 1) {
                    if (j == m_uni_size - 1) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                0)->vectors.at(0)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(
                                0)->vectors.at(j + 1)->magnitude;
                    }
                } else {
                    if (j == m_uni_size - 1) {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i + 1)->vectors.at(
                                0)->magnitude;
                    } else {
                        tempField->lines.at(i)->vectors.at(j)->magnitude += lines.at(i + 1)->vectors.at(
                                j + 1)->magnitude;
                    }
                }
            }
        }
        for (int i = 0; i < m_uni_size; i++) {
            for (int j = 0; j < m_uni_size; j++) {
                lines.at(i)->vectors.at(j)->magnitude = tempField->lines.at(i)->vectors.at(j)->magnitude / 9;
            }
        }
        delete tempField;
    }

    void propagateMagnitudesWithRolling(){

    }

    ~Field(){
        for(auto line : lines){
            for(auto vec : line->vectors){
                delete vec;
            }
            delete line;
        }
//        delete this;
    }



    void print() {

#ifdef DEBUG
        for (WorldLine *line : lines) {
            for (Vec4 *vec : line->vectors) {
                std::cout << "(" << vec->x << "," << vec->y << "," << vec->magnitude << "," << vec->d << ")";
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
        uint32_t universeSize;
        uint64_t universeVolume;

        explicit Physics(uint32_t a_universeSize) {
            universeSize = a_universeSize;
            universeVolume = universeSize * universeSize;
            initGravity();
        }

        void tick() {
            using namespace std::chrono;
//            gravity.print();
            auto start = std::chrono::high_resolution_clock::now();
            gravity.propagateMagnitudes();
//            gravity.print();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);

// To get the value of duration use the count()
// member function on the duration object
            std::cout << duration.count() << std::endl;
        }

    private:

        void initGravity() {
            for (uint32_t x = 0; x < universeSize; x++) {
                auto *line = new WorldLine();
                gravity.lines.push_back(line);
                for (uint32_t y = 0; y < universeSize; y++) {
                    gravity.lines.at(x)->vectors.push_back(new Vec4{x, y, 0, 0});
                }
            }
            gravity.lines.at(5)->vectors.at(5)->magnitude = 5000;
            gravity.lines.at(2)->vectors.at(2)->magnitude = 5000;
            gravity.lines.at(9)->vectors.at(9)->magnitude = 5000;
        }

    };
}

//TEST_CASE();

#endif //DUST_PHYSICS_H
