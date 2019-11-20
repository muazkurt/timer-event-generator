cmake_minimum_required(VERSION 3.9.1)
# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

project(Muaz_Kurt_Timer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(header)

add_library(timer SHARED source/Timer.cpp source/Event.cpp source/ThreadGuard.cpp source/FileGuard.cpp)

