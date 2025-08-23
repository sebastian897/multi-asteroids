function run() {
    ./main &
    ./client &
    ./client
}


make &&
# gcc -Wall -Wextra -std=c11 -o server -IC:/raylib/raylib/src -LC:/raylib/raylib/src \
#   src/serve.c src/server.c src/netif.c src/asteroid.c  -lws2_32 -lraylib -lopengl32 -lgdi32 -lwinmm && \
gcc -Wall -Wextra -std=c11 -o client -IC:/raylib/raylib/src -LC:/raylib/raylib/src \
  client/clien.c client/client.c src/asteroid.c -lws2_32 -lraylib -lopengl32 -lgdi32 -lwinmm && \
# run
