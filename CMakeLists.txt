cmake_minimum_required(VERSION 3.17)
project(brainfuck_compiler)

set(CMAKE_CXX_STANDARD 17)
option(ENABLE_CONAN "Enable Conan" OFF)

set(SOURCES
    src/main.cpp
    src/Compile.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

#---
include_directories(include)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if (ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  conan_target_link_libraries(${PROJECT_NAME} PRIVATE
      CONAN_PKG::fmt
      CONAN_PKG::gtest
      )
endif ()
