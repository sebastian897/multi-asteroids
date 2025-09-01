#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "constants.h"
#include "game.h"
#include "game_asteroids.h"
#include "server.h"
#include <string.h>
#include <stdio.h>
#include "game_player.h"

void UpdateDrawFrame(void);

bool _quitGame = false;

#define BUFSIZE 1024

int main(){
	ServerInit();
    SetRandomSeed(time(0));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Server");

	InitGame();
	_playerId = -2;

	while(!WindowShouldClose() && !_quitGame)
	{
		UpdateDrawFrame();
		ReceiveMultiple();
        char buf[BUFSIZE];
        memcpy(buf+sizeof(unsigned char), &_asteroids, sizeof(Asteroid)*ASTEROID_MAX);
        memcpy(buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX, &_players, sizeof(Player)*PLAYERS_MAX);
		int count = 0;
        for (int i = 0; i < ASTEROID_MAX; i++){
            if (_asteroids[i].active){
                count++;
            }
        }
		
        printf("Server: Number of asteroids sent: %d", count);
        Broadcast(buf, sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX+sizeof(Player)*PLAYERS_MAX);
	}
	
	CloseWindow();
    ServerShutdown(); 
	
	return 0;
}

void UpdateDrawFrame(void)
{
	UpdateGame();

	BeginDrawing();

	ClearBackground(NEARBLACK);

	DrawGame();

	EndDrawing();
}