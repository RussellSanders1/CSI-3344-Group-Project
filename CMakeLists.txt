cmake_minimum_required(VERSION 3.9)

project(SDLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories("${PROJECT_SOURCE_DIR}/SDL2")
link_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(test point.h point.cpp color_rgb.h color_rgb.cpp
        SDL_Plotter.h SDL_Plotter.cpp test.cpp curve.cpp curve.h line.h line.cpp)
target_link_libraries(test SDL2main SDL2 SDL2_mixer)

add_executable(DivideConquer point.h point.cpp color_rgb.h color_rgb.cpp
        SDL_Plotter.h SDL_Plotter.cpp line.h line.cpp)
target_link_libraries(DivideConquer SDL2main SDL2 SDL2_mixer)