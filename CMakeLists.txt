cmake_minimum_required(VERSION 3.5)

project(epidemic-simulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARY SDL2_image)

add_executable(epidemic-simulation  main.cpp
                                    game.hpp
                                    game.cpp
                                    people.hpp
                                    people.cpp)

target_link_libraries(epidemic-simulation ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
