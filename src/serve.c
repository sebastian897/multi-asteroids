#include "server.h"
#include "netif.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define BUFSIZE 512

int main() {
    ServerInit();
    SetRandomSeed(time(0));
    Vector2 pos = {0.0,0.0};
    Vector2 vel = {0.0,0.0};
    Asteroid asteroid = CreateAsteroid(pos,vel,ASTEROID_SMALL);    
    while (true){
        Receive();
        printf("Server: sending asteroid\n");
        PrintAsteroid(&asteroid);

        char buf[BUFSIZE];
        memcpy(buf, &asteroid, sizeof(asteroid));
        Broadcast(buf, sizeof(asteroid));
    }
    ServerShutdown();    
}