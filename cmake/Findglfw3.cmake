set(FIND_GLFW_PATHS ${CMAKE_SOURCE_DIR}/dependencies/glfw/lib-vc2017)

find_path(GLFW_INCLUDE_DIR glfw3.h
        PATH_SUFFIXES include
        PATHS ${FIND_GLFW_PATHS})

find_library(GLFW_LIBRARY NAMES libglfw3
        PATH_SUFFIXES lib
        PATHS ${FIND_GLFW_PATHS})