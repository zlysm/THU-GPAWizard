cmake_minimum_required(VERSION 3.22)
project(GPAWizard)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

aux_source_directory(src SRC_FILES)

add_executable(GPAWizard ${SRC_FILES})

file(COPY ${CMAKE_SOURCE_DIR}/shared DESTINATION ${CMAKE_BINARY_DIR})