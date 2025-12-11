cmake_minimum_required(VERSION 3.16)
project(UdsComm C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/pltf
    ${CMAKE_CURRENT_SOURCE_DIR}/cfg
)

# Automatically collect sources
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/pltf/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cfg/*.c"
)

add_library(udscomm STATIC ${SOURCES})