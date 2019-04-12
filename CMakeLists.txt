cmake_minimum_required(VERSION 3.9)

project(SDLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(BruteForce main.cpp point.h point.cpp color_rgb.h color_rgb.cpp
        SDL_Plotter.h SDL_Plotter.cpp)
target_link_libraries(BruteForce SDL2main SDL2 SDL2_mixer)