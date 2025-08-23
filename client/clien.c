#include "client.h"
#include "netif.h"
#include <string.h>
#include <stdio.h>
#include "../src/constants.h"

Asteroid _asteroids[ASTEROID_MAX] = {0};


int main(){
    ClientInit();
    printf("Client Starting..\n");
    Send("big gay", 8);
    while (1){
        ClientReceive();
        memcpy(&_asteroids, buf, sizeof(Asteroid)*ASTEROID_MAX);
        int count = 0;
        for (int i = 0; i < ASTEROID_MAX; i++){
            if (_asteroids[i].active){
                count++;
            }
        }
        printf("Client: Number of asteroids received: %d\n", count);
    }
    ClientShutdown();
}