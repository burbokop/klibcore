cmake_minimum_required(VERSION 3.7)
project(KLibCore)

message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(klibcore.cmake)
