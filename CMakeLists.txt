# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(chygak_lab)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
    src
)

set (SRCS
    src/lib.cpp
    src/lib_realiz.cpp
)

set (TESTS
    tests/test.cpp
)

add_library(pilo_lib SHARED ${SRCS})
add_executable(${PROJECT_NAME}_test ${TESTS})
target_link_libraries(${PROJECT_NAME}_test pilo_lib)

add_custom_target(tests ${PROJECT_NAME}_test)
