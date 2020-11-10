cmake_minimum_required(VERSION 3.15)
project(Solving_differential_equations)

set(CMAKE_CXX_STANDARD 14)

add_executable(Solving_differential_equations main.cpp cmath.h rkf45.c)