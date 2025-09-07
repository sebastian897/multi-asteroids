function run() {
    ./main &
    ./client &
    ./client
}

gcc -c src/asteroid.c -o svr_obj/asteroid.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/debug.c -o svr_obj/debug.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/debug_cones.c -o svr_obj/debug_cones.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c server/game.c -o svr_obj/game.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_asteroids.c -o svr_obj/game_asteroids.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c server/game_player.c -o svr_obj/game_player.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_projectiles.c -o svr_obj/game_projectiles.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_score.c -o svr_obj/game_score.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c server/game_ui.c -o svr_obj/game_ui.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c server/main.c -o svr_obj/main.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/player.c -o svr_obj/player.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/projectile.c -o svr_obj/projectile.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/raygui.c -o svr_obj/raygui.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c server/server.c -o svr_obj/server.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -o main.exe svr_obj/asteroid.o svr_obj/debug.o svr_obj/debug_cones.o svr_obj/game.o svr_obj/game_asteroids.o svr_obj/game_player.o \
  svr_obj/game_projectiles.o svr_obj/game_score.o svr_obj/game_ui.o svr_obj/main.o svr_obj/player.o svr_obj/projectile.o svr_obj/raygui.o\
  svr_obj/server.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1 -I. -IC:/raylib/raylib/src\
  -IC:/raylib/raylib/src/external -L. -LC:/raylib/raylib/src -LC:/raylib/raylib/src \
  C:/raylib/raylib/src/raylib.rc.data -Wl,--subsystem,windows -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32 \
  -DPLATFORM_DESKTOP

gcc -c src/asteroid.c -o clt_obj/asteroid.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/debug.c -o clt_obj/debug.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/debug_cones.c -o clt_obj/debug_cones.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c client/game.c -o clt_obj/game.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_asteroids.c -o clt_obj/game_asteroids.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c client/game_player.c -o clt_obj/game_player.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_projectiles.c -o clt_obj/game_projectiles.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/game_score.c -o clt_obj/game_score.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c client/game_ui.c -o clt_obj/game_ui.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -Isrc -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/player.c -o clt_obj/player.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/projectile.c -o clt_obj/projectile.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP
gcc -c src/raygui.c -o clt_obj/raygui.o -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1\
    -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP

gcc -c client/clien.c -o clt_obj/clien.o -Wall -Wextra -std=c11 -Wno-missing-braces \
  -s -O1 -Isrc -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP

gcc -c client/client.c -o clt_obj/client.o -Wall -Wextra -std=c11 -Wno-missing-braces \
  -s -O1 -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP

gcc -o client.exe clt_obj/asteroid.o clt_obj/clien.o clt_obj/client.o clt_obj/debug.o clt_obj/debug_cones.o clt_obj/game.o \
  clt_obj/game_asteroids.o clt_obj/game_player.o clt_obj/game_projectiles.o clt_obj/game_score.o \
  clt_obj/game_ui.o clt_obj/player.o clt_obj/projectile.o clt_obj/raygui.o \
  -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1 -I. -IC:/raylib/raylib/src \
  -IC:/raylib/raylib/src/external -L. -LC:/raylib/raylib/src -LC:/raylib/raylib/src \
  C:/raylib/raylib/src/raylib.rc.data -Wl,--subsystem,windows \
  -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32 -DPLATFORM_DESKTOP


