#include "client.h"
#include "netif.h"
#include <string.h>
#include <stdio.h>

int main(){
    ClientInit();
    Send("big gay", 8);
    ClientReceive();
    Asteroid asteroid;
    memcpy(&asteroid, buf, sizeof(asteroid));
    printf("CLient: receiving asteroid\n");
    PrintAsteroid(&asteroid);

    ClientShutdown();
}