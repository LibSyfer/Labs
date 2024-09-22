cmake_minimum_required(VERSION 3.1)

project(oop_exercise_01)

add_executable(oop_exercise_01 main.cpp bigString.cpp)

set_property(TARGET oop_exercise_01 PROPERTY CXX_STANDART 11) 
