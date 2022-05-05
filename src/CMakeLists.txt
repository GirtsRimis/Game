add_library(
    game_lib
    movableEntity.cpp
    particleSystem.cpp
    player.cpp
    tileMap.cpp
    levels.cpp
)

target_include_directories(game_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
