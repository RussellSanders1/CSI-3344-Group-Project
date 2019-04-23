cmake_minimum_required(VERSION 3.9)

project(SDLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(divideConquer dividehull-driver.cpp divideHullFunctions.cpp
        constants.h divideHullFunctions.h point.cpp point.h circle.h
        circle.cpp color_rgb.cpp color_rgb.h line.cpp line.h
        plotterFunctions.cpp plotterFunctions.h font.h font.cpp
        bruteHullFunctions.h bruteHullFunctions.cpp
        SDL_Plotter.h SDL_Plotter.cpp)
target_link_libraries(divideConquer SDL2main SDL2 SDL2_mixer)