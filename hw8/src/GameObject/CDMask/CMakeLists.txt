cmake_minimum_required(VERSION 3.16)

add_library(
  CDMask
  STATIC
  CDMask.hpp
  CDMask.cpp
)

target_link_libraries(
  CDMask
  GameObject
  GameWorld
  Framework
)

target_include_directories(
  CDMask
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameObject/CDMask/
)
