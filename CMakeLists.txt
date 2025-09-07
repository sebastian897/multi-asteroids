cmake_minimum_required(VERSION 3.28)
project(multi-asteroid)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POST_CONFIGURE_SCRIPT "${CMAKE_SOURCE_DIR}/cmake/CopyCompileCommands.cmake")

set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5  # or a specific commit
)

FetchContent_MakeAvailable(raylib)

add_library(multi-asteroid-common 
    src/asteroid.c
    src/debug.c  
    src/debug_cones.c  
    src/game_asteroids.c  
    src/game_projectiles.c  
    src/game_score.c  
    src/player.c  
    src/projectile.c  
    src/raygui.c)

target_link_libraries(multi-asteroid-common PRIVATE raylib)
target_include_directories(multi-asteroid-common INTERFACE src)
target_compile_features(multi-asteroid-common INTERFACE c_std_23)
target_compile_options(multi-asteroid-common PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

add_executable(server 
    server/buffer_control.c  
    server/game.c  
    server/game_player.c  
    server/game_ui.c  
    server/main.c  
    server/server.c
)

target_compile_features(server INTERFACE c_std_23)
target_link_libraries(server PRIVATE 
    raylib  
    multi-asteroid-common)
if(WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()

target_compile_options(server PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

add_executable(client 
    client/clien.c
    client/client.c
    client/game.c
    client/game_player.c
    client/game_ui.c
    client/netif.c
)

target_compile_features(client INTERFACE c_std_23)
target_link_libraries(client PRIVATE 
    raylib  
    multi-asteroid-common)
if(WIN32)
    target_link_libraries(client PRIVATE ws2_32)
endif()

target_compile_options(client PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

