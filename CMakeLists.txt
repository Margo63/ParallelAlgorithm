cmake_minimum_required(VERSION 3.25)
project(lab1_par_alg)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_par_alg threadP.cpp  matrix.cpp matrix.h )
