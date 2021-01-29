//
// Created by Amy on 12/31/2020.
//
#pragma once
#ifndef DUST_LOGGER_H
#define DUST_LOGGER_H

#include <chrono>

namespace Logger {
    enum class ErrorType {
        OPEN_GL_ERROR = 0, PHYSICS_ERROR = 1
    };

    template<typename T>
    static void debug(const T &x) {
        #if DEBUG==1
        std::cout << "DEBUG: " << x << std::endl;
        #endif
    };

    template<typename T>
    static void debug(const T &x, const std::string &message) {
        #if DEBUG==1
        std::cout << "DEBUG: " << x << " " << message.c_str() << std::endl;
        #endif
    };

    template<typename T>
    static void debug(const std::string &message) {
        #if DEBUG==1
        std::cout << "DEBUG: " << message.c_str() << std::endl;
        #endif
    };

    template<typename T>
    static void info(const T &x) {
        #if DEBUG==1
        std::cout << "INFO: " << x << std::endl;
        #endif
    };

    template<typename T>
    static void info(const T &x, const std::string &message) {
        #if DEBUG==1
        std::cout << "INFO: " << x << " " << message.c_str() << std::endl;
        #endif
    };

    template<typename T>
    static void info(const std::string &message) {
        #if DEBUG==1
        std::cout << "INFO: " << message.c_str() << std::endl;
        #endif
    };

    template<typename T>
    static void err(ErrorType type, T message) {
        std::string text;
        switch (type) {
            case (ErrorType::OPEN_GL_ERROR):
                text = "Open GL Error";
                break;
            case (ErrorType::PHYSICS_ERROR):
                text = "Physics Error";
                break;
            default:
                text = "General Error";
                break;
        }

        std::cout << text.c_str() << ": " << message << std::endl;
    }

    class Timer {
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> stop;
        std::chrono::time_point<std::chrono::steady_clock> lastTick;

        long countTotal = 0;
        long double tickTotal = 0;
        bool printOnDeath = false;
        std::string message;

//        std::chrono::high_resolution_clock::now()
        std::chrono::microseconds currentDuration() {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start);;
        }




    public:
        ~Timer() {

            #if DEBUG==1
            if (printOnDeath) {
                if (!message.empty()) {
                    std::cout << "Timer " << message.c_str() << " " << currentDuration().count() << "us" << std::endl;
                }else {
                    std::cout << currentDuration().count() << "us" << std::endl;
                }

            }
            #endif

        }

        //        std::chrono::duration duration = duration_cast<std::chrono::microseconds>(stop - start);
        explicit Timer(bool print, const std::string &_message = "") {
            message = _message;
            start = std::chrono::high_resolution_clock::now();
            lastTick = std::chrono::high_resolution_clock::now();
            printOnDeath = print;
        }

        void reset() {
            start = std::chrono::high_resolution_clock::now();
        }

        void tick(){
            countTotal += std::chrono::duration_cast<std::chrono::microseconds>((std::chrono::high_resolution_clock::now() - lastTick)).count();
            lastTick = std::chrono::high_resolution_clock::now();
            tickTotal++;
        }

        long getAverage(){
            return countTotal/tickTotal;
        }

        void finish() {
            stop = std::chrono::high_resolution_clock::now();
            std::cout << currentDuration().count() << "us" << std::endl;
        }

        void print(){
            #if DEBUG==1
            if (!message.empty()) {
                std::cout << "Timer " << message.c_str() << " " << currentDuration().count() << "us" << std::endl;
            }else {
                std::cout << currentDuration().count() << "us" << std::endl;
            }
            #endif
        }

        void printAverage(){
            #if DEBUG==1
            if (!message.empty()) {
                std::cout << "Timer " << message.c_str() << " " << getAverage() << "us" << std::endl;
            }else {
                std::cout << currentDuration().count() << "us" << std::endl;
            }
            #endif
        }
    };


}



#endif //DUST_LOGGER_H
