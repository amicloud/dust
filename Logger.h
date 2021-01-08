//
// Created by Amy on 12/31/2020.
//
#pragma once
#ifndef DUST_LOGGER_H
#define DUST_LOGGER_H

namespace Logger {
    template<typename T>
    static inline void log(const T &x){
        std::cout << "DEBUG: " << x << std::endl;
    };

     void err(uint32_t err);
}

#endif //DUST_LOGGER_H
