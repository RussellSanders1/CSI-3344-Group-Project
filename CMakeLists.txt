cmake_minimum_required(VERSION 3.9)

project(SDLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(SDLTest main.cpp SDL_Plotter.h SDL_Plotter.cpp color_rgb.h
        color_rgb.cpp curve.h curve.cpp line.h line.cpp point.h point.cpp )
target_link_libraries(SDLTest SDL2main SDL2 SDL2_mixer)

add_executable(test test.cpp SDL_Plotter.h SDL_Plotter.cpp color_rgb.h
        color_rgb.cpp curve.h curve.cpp line.h line.cpp point.h point.cpp)
target_link_libraries(test SDL2main SDL2 SDL2_mixer)
