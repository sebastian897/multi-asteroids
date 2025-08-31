#include "client.h"
#include "netif.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "../src/game_player.h"
#include "../src/constants.h"
#include "../src/game.h"
#include "../src/game_asteroids.h"

bool _quitGame = false;

#define BUFSIZE 1024

void UpdateDrawFrame(void)
{
	UpdateGame();

	BeginDrawing();

    ClearBackground(NEARBLACK);

    DrawGame();

	EndDrawing();
}

int main(){
    ClientInit();
    printf("Client Starting..\n");
    Send("Client first packet", 20);

    SetRandomSeed(time(0));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Client");

	InitGame();

	while(!WindowShouldClose() && !_quitGame)
	{
        ClientReceive();
        memcpy(&_playerId, buf, 1);
        _players[_playerId].active = 1;
        memcpy(&_asteroids, buf+1, sizeof(Asteroid)*ASTEROID_MAX);
        int count = 0;
        for (int i = 0; i < ASTEROID_MAX; i++){
            if (_asteroids[i].active){
                count++;
            }
        }
        // printf("Client: id = %d", _playerId);
        printf("Client: Number of asteroids received: %d\n", count);
		UpdateDrawFrame();
    }
    _players[_playerId].active = 0;
	CloseWindow();
    ClientShutdown();
}