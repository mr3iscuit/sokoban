cmake_minimum_required(VERSION 3.13.1)

project(sokoban)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_custom_target(copy_levels
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)
add_executable(sokoban Entity.cpp EntityWithCollision.cpp Game.cpp LevelManager.cpp main.cpp)
target_link_libraries(sokoban SDL2 SDL2_image SDL2_ttf)
add_dependencies(sokoban copy_assets copy_levels)
