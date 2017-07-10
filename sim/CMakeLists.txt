# Neomatrix - Copyright (C) 2017 Lars Christensen
# MIT Licensed
cmake_minimum_required(VERSION 3.6)
project(matrix)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-scripts")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories(. ../app)
add_executable(matrix
  matrix.cpp
  matrix.hpp
  ../src/coord.cpp ../src/coord.hpp
  # ../src/balls.cpp
  # ../src/balls.hpp
  ../src/common.cpp
  ../src/common.hpp
  # ../src/fire.cpp
  # ../src/fire.hpp
  # ../src/lemmings.cpp
  # ../src/lemmings.hpp
  ../src/framelimiter.cpp
  ../src/framelimiter.hpp
  ../src/hsv2rgb.cpp
  ../src/hsv2rgb.hpp
  # ../src/matrix.cpp
  # ../src/matrix.hpp
  # ../src/metaballs.cpp
  # ../src/metaballs.hpp
  # ../src/moire.cpp
  # ../src/moire.hpp
  ../src/program.cpp
  ../src/program.hpp
  ../src/text.cpp
  ../src/text.hpp
  ../src/neomatrix.cpp
  ../src/neomatrix.hpp
  ../src/hal9k.cpp
  ../src/hal9k-glitter.cpp
  ../src/hal9k-rainbow.cpp
  ../src/hal9k-wipe.cpp
  ../src/hal9k-letter.cpp
  ../src/hal9k-paint.cpp
  )
target_link_libraries(matrix ${SDL2_LIBRARY})
