cmake_minimum_required(VERSION 3.19)
project(measures)

set(CMAKE_CXX_STANDARD 14)

add_executable(measures main.cpp messw/messw.cpp messw/messw.h fraction/fraction.cpp fraction/fraction.h)