cmake_minimum_required(VERSION 3.6)
project(matrix)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../sdl2-cmake-scripts")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories(. ../app)
add_executable(matrix
  matrix.cpp
  matrix.hpp
  ../src/balls.cpp
  ../src/balls.hpp
  ../src/common.cpp
  ../src/common.hpp
  ../src/fire.cpp
  ../src/fire.hpp
  ../src/framelimiter.cpp
  ../src/framelimiter.hpp
  ../src/matrix.cpp
  ../src/matrix.hpp
  ../src/metaballs.cpp
  ../src/metaballs.hpp
  ../src/moire.cpp
  ../src/moire.hpp
  ../src/program.cpp
  ../src/program.hpp
  ../src/neomatrix.cpp
  ../src/neomatrix.hpp
  # logo.rgb
  )
# add_custom_command(OUTPUT logo.rgb COMMAND cmake -E copy_if_different "${CMAKE_SOURCE_DIR}/../files/logo.rgb" "logo.rgb")
target_link_libraries(matrix ${SDL2_LIBRARY})
