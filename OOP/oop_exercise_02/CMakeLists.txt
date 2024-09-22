cmake_minimum_required(VERSION 3.1)
set(MAIN_CPP source/main.cpp)
set(BIGSTRING_CPP source/bigString.cpp)

project(oop_exercise_02)

add_executable(oop_exercise_02 ${MAIN_CPP} ${BIGSTRING_CPP})

set_property(TARGET oop_exercise_02 PROPERTY CXX_STANDART 11)
