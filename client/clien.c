#include "client.h"
#include "netif.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "game_player.h"
#include "constants.h"
#include "game.h"
#include "game_asteroids.h"

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
        memcpy(&_asteroids, buf+sizeof(unsigned char), sizeof(Asteroid)*ASTEROID_MAX);
        memcpy(&_players, buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX, sizeof(Player)*PLAYERS_MAX);
        int count = 0;
        for (int i = 0; i < ASTEROID_MAX; i++){
            if (_asteroids[i].active){
                count++;
            }
        }
        bool thrust = IsKeyDown(KEY_UP);
        signed char rotation = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
        memcpy(buf, &_playerId, 1);        
        memcpy(buf+sizeof(_playerId), &thrust, sizeof(thrust));
        memcpy(buf+sizeof(_playerId)+sizeof(thrust), &rotation, sizeof(rotation));
        
        printf("Client: inputs sending: %d %d %d\n", (signed char)buf[0], (bool)buf[1], (signed char)buf[2]);
        Send(buf, sizeof(_playerId)+sizeof(thrust)+sizeof(rotation));

        // printf("Client: id = %d", _playerId);
		UpdateDrawFrame();
    }
    _players[_playerId].active = 0;
	CloseWindow();
    ClientShutdown();
}