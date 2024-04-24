cmake_minimum_required(VERSION 3.16)

add_library(
  Sun
  STATIC
  Sun.hpp
  Sun.cpp
)

target_link_libraries(
  Sun
  GameObject
  GameWorld
  Framework
)

target_include_directories(
  Seed
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Sun/
)
