cmake_minimum_required(VERSION 3.19)

file(GLOB ${PROJECT_NAME}_TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/ioutils/*.cpp
)

add_executable(${PROJECT_NAME}_tests
    ${${PROJECT_NAME}_TEST_SOURCES}
)

target_link_libraries(${PROJECT_NAME}_tests
    ioutils
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)