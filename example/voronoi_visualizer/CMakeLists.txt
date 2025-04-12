cmake_minimum_required(VERSION 3.17)

project(voronoi_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")

find_package(Qt5 COMPONENTS Core OpenGL Widgets REQUIRED PATHS /opt/homebrew/opt/qt@5)

include_directories(
  /opt/homebrew/opt/qt@5/include
  /Users/wangchao/dev/computational-geometry/boost_org/boost
)

add_executable(voronoi_visualizer
  voronoi_visualizer.cpp
  voronoi_visual_utils.hpp
)

target_compile_definitions(voronoi_visualizer PRIVATE GL_SILENCE_DEPRECATION)

target_link_libraries(voronoi_visualizer
  Qt5::Core
  Qt5::OpenGL
  Qt5::Widgets
  "-framework OpenGL"
)

install(TARGETS voronoi_visualizer DESTINATION bin)
