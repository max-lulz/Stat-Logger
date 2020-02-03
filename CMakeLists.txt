cmake_minimum_required(VERSION 3.10.2)

project(StatLogger)

add_executable(StatLogger.out main.cpp ProcessDataHandler.cpp ProcessDataHandler.h)

add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(StatLogger.out ${CPR_LIBRARIES})