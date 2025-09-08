cmake_minimum_required(VERSION 3.28)
project(multi-asteroid)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

function(setup_target_warnings_and_sanitizers target)
    target_compile_options(${target} PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
        $<$<C_COMPILER_ID:MSVC>:/W4>
    )
    set(SANITIZER_EXPR $<$<AND:$<C_COMPILER_ID:GNU,Clang>,$<NOT:$<PLATFORM_ID:Windows>>,$<CONFIG:Debug>>:-fsanitize=address,undefined,leak>)
    target_compile_options(${target} PRIVATE ${SANITIZER_EXPR})
    target_link_options(${target} PRIVATE ${SANITIZER_EXPR})
endfunction()

function(opt_link_winsock target)
  if(WIN32)
    target_link_libraries(${target} PRIVATE ws2_32)
  endif()
endfunction()

# fetch an compile raylib
include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5  # or a specific commit
)

FetchContent_MakeAvailable(raylib)

# compile a "common" library which will be used from both server and client
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
setup_target_warnings_and_sanitizers(multi-asteroid-common)

# compile the server
add_executable(server 
    server/buffer_control.c  
    server/game.c  
    server/game_player.c  
    server/game_ui.c  
    server/main.c  
    server/server.c
)

target_compile_features(server INTERFACE c_std_23)
target_link_libraries(server PRIVATE raylib multi-asteroid-common)
opt_link_winsock(server)
setup_target_warnings_and_sanitizers(server)

# compile the client
add_executable(client 
    client/clien.c
    client/client.c
    client/game.c
    client/game_player.c
    client/game_ui.c
    client/netif.c
)

target_compile_features(client INTERFACE c_std_23)
target_link_libraries(client PRIVATE raylib multi-asteroid-common)
opt_link_winsock(client)
setup_target_warnings_and_sanitizers(client)

# copy compile_commands.json from the build dir to the source dir
add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/compile_commands.json"
        "${CMAKE_SOURCE_DIR}/compile_commands.json"
    COMMENT "Copying compile_commands.json to source root"
)
