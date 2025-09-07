#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "constants.h"
#include "game.h"
#include "game_asteroids.h"
#include "game_projectiles.h"
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
		char buf[BUFSIZE];

		ReceiveMultiple();


		UpdateDrawFrame();

        memcpy(buf+sizeof(unsigned char), &_asteroids, sizeof(Asteroid)*ASTEROID_MAX);
        memcpy(buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX, &_players, sizeof(Player)*PLAYERS_MAX);
		memcpy(buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX+sizeof(Player)*PLAYERS_MAX, &_projectiles, sizeof(Projectile)*PROJECTILE_MAX);

        Broadcast(buf, sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX+sizeof(Player)*PLAYERS_MAX+sizeof(Projectile)*PROJECTILE_MAX);
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