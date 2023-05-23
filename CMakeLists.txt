cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(Pixie)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
FetchContent_Declare(
  gvdi
  GIT_REPOSITORY https://github.com/karnkaul/gvdi
  GIT_TAG 77db1bd
)
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG ac13ca9
)
FetchContent_MakeAvailable(gvdi)
FetchContent_MakeAvailable(SDL2)
add_executable(${PROJECT_NAME})
add_compile_options(-Wall -Wextra -pedantic)
include_directories(${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/sdl2-src/include)
target_link_libraries(${PROJECT_NAME} PRIVATE gvdi::gvdi)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
target_sources(${PROJECT_NAME} PRIVATE 
  src/editor.cpp
  src/export.cpp
  src/main.cpp
  src/window.cpp
  src/rng.cpp
)
