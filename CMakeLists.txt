cmake_minimum_required(VERSION 3.20)
project(Rhombus CXX)

set(Rhombus_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/source/include")
set(Rhombus_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")

add_executable(Rhombus)

target_sources(
    Rhombus PRIVATE

    # sources
    "${Rhombus_SOURCE_DIR}/rhombus.cpp"
    "${Rhombus_SOURCE_DIR}/parser.cpp"    

    # headers
    "${Rhombus_INCLUDE_DIR}/parser.hpp"
)
