cmake_minimum_required(VERSION 3.12)

project(ehsm-util-c)

enable_language(C)

set(CMAKE_C_STANDARD 99)

add_library(ehsm-util-c
        include/ehsm-c-util.h
        src/util.c)

target_include_directories(ehsm-util-c
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
