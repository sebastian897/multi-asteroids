function run() {
    ./main &
    ./client &
    ./client
}


make &&
# gcc -Wall -Wextra -std=c11 -o server -IC:/raylib/raylib/src -LC:/raylib/raylib/src \
#   src/serve.c src/server.c src/netif.c src/asteroid.c  -lws2_32 -lraylib -lopengl32 -lgdi32 -lwinmm && \
# gcc -Wall -Wextra -std=c11 -o client -IC:/raylib/raylib/src -LC:/raylib/raylib/src \
#   client/clien.c client/client.c -lws2_32 -lraylib -lopengl32 -lgdi32 -lwinmm 
gcc -c client/clien.c -o obj/clien.o -Wall -Wextra -std=c11 -Wno-missing-braces \
  -s -O1 -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP

gcc -c client/client.c -o obj/client.o -Wall -Wextra -std=c11 -Wno-missing-braces \
  -s -O1 -I. -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -DPLATFORM_DESKTOP

gcc -o client.exe obj/asteroid.o obj/clien.o obj/client.o obj/debug.o obj/debug_cones.o obj/game.o \
  obj/game_asteroids.o obj/game_player.o obj/game_projectiles.o obj/game_score.o \
  obj/game_ui.o obj/player.o obj/projectile.o obj/raygui.o \
  -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1 -I. -IC:/raylib/raylib/src \
  -IC:/raylib/raylib/src/external -L. -LC:/raylib/raylib/src -LC:/raylib/raylib/src \
  C:/raylib/raylib/src/raylib.rc.data -Wl,--subsystem,windows \
  -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32 -DPLATFORM_DESKTOP