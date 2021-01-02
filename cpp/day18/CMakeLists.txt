cmake_minimum_required(VERSION 3.19)

add_executable(day18 main.cxx)

target_link_libraries(day18 PRIVATE ioutils)

file(GLOB INPUTFILES input.txt)
foreach(input IN LISTS INPUTFILES)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
