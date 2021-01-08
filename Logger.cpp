//
// Created by Amy on 12/31/2020.
//
#pragma once
#ifndef DUST_LOGGER_H
#define DUST_LOGGER_H
#include <iostream>
//#include "Dust.h"

namespace Logger {

    void err(uint32_t err) {
        std::cout << "Open GL error: " << err << std::endl;
    }
}

#include "Logger.h"
#endif //DUST_LOGGER_H
//
// Created by Amy on 12/31/2020.
//

