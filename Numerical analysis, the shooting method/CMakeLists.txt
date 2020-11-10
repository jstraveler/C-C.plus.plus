cmake_minimum_required(VERSION 3.15)
project(Numerical_analysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(Numerical_analysis main.cpp rkf45.c cmath.h zeroin.c quanc8.c decomp.cpp)