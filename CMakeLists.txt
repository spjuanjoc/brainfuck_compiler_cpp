cmake_minimum_required(VERSION 3.17)
project(brainfuck_compiler)

set(CMAKE_CXX_STANDARD 17)
option(ENABLE_CONAN "Enable Conan" OFF)

# Setup file extensions for platform specific sources: Linux, Windows, and Apple (Darwin)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux") # .cc .hh
  set(PLATFORM_EXTENSION cc)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows") # .cxx .hxx
#  set(PLATFORM_EXTENSION cxx)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # .mm .h
#  set(PLATFORM_EXTENSION mm)
endif()

set(SOURCES
    src/main.cpp
    src/Compile.cpp
    src/Assemble.${PLATFORM_EXTENSION}
    src/Link.${PLATFORM_EXTENSION}
    src/Exec.${PLATFORM_EXTENSION}
    src/Run.${PLATFORM_EXTENSION}
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
