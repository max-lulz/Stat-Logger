cmake_minimum_required(VERSION 3.10.2)

project(StatLogger)

add_executable(StatLogger.out main.cpp ProcessDataHandler/ProcessDataHandler.cpp ProcessDataHandler/ProcessDataHandler.h)

add_subdirectory(cpr)
add_subdirectory(ProcessDataHandler)

include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(StatLogger.out ${CPR_LIBRARIES} ${PROJECT_BINARY_DIR}  ${PROJECT_SOURCE_DIR}/ProcessDataHandler)