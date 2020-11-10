cmake_minimum_required(VERSION 3.13)
project(Solving_systems_of_linear_equations)

set(CMAKE_CXX_STANDARD 14)

add_executable(Solving_systems_of_linear_equations main.cpp cmath.h cmathmsg.c decomp.cpp)