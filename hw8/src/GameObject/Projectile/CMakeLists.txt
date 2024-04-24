cmake_minimum_required(VERSION 3.16)

add_library(
  Projectile
  STATIC
  Projectile.hpp
  Projectile.cpp
)

target_link_libraries(
  Projectile
  GameObject
  GameWorld
  Framework
)

target_include_directories(
  Plant
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Projectile/
)
