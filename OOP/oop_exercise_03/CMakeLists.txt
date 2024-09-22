cmake_minimum_required(VERSION 3.1)
set(MAIN_CPP source/main.cpp)
set(FIGURE_CPP source/Figure.cpp)
set(HEXAGON_CPP source/Hexagon.cpp)
set(OCTAGON_CPP source/Octagon.cpp)
set(TRIANGLE_CPP source/Triangle.cpp)

project(oop_exercise_03)

add_executable(oop_exercise_03 ${MAIN_CPP} ${FIGURE_CPP} ${HEXAGON_CPP} ${OCTAGON_CPP} ${TRIANGLE_CPP})

set_property(TARGET oop_exercise_03 PROPERTY CXX_STANDART 11)
