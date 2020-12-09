cmake_minimum_required(VERSION 3.19)

project(AoC VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(iolib INTERFACE)
target_include_directories(iolib INTERFACE ioutils/)

