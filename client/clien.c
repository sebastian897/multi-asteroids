#include "client.h"
#include "netif.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"

#include "game_player.h"
#include "constants.h"
#include "game.h"
#include "game_asteroids.h"
#include "game_projectiles.h"

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

int main(void){
  ClientInit();
  printf("Client Starting..\n");
  ClientInit();
  bool inputsPacket = false;
  char* msg = "Client first packet";
  memcpy(buf, &inputsPacket, sizeof(inputsPacket));        
  memcpy(buf+sizeof(inputsPacket), &msg, strlen(msg));        
  Send(buf, strlen(msg)+sizeof(inputsPacket));

  SetRandomSeed(time(0));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Client");

	InitGame();
  inputsPacket = true;
	while(!WindowShouldClose() && !_quitGame)
	{
    // printf("Client Receiving..\n");
    ClientReceive();
    // printf("Client Received..\n");
    memcpy(&_playerId, buf, 1);
    _players[_playerId].active = 1;
    
    memcpy(&_asteroids, buf+sizeof(unsigned char), sizeof(Asteroid)*ASTEROID_MAX);
    memcpy(&_players, buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX, sizeof(Player)*PLAYERS_MAX);
    memcpy(&_projectiles, buf+sizeof(unsigned char)+sizeof(Asteroid)*ASTEROID_MAX+sizeof(Player)*PLAYERS_MAX, sizeof(Projectile)*PROJECTILE_MAX);
    
    bool thrust = IsKeyDown(KEY_UP);
    bool shooting = IsKeyDown(KEY_SPACE);
    signed char rotation = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    memcpy(buf, &inputsPacket, sizeof(inputsPacket));        
    // printf("PlayerId sent: %d", _playerId);
    memcpy(buf+sizeof(inputsPacket), &_playerId, sizeof(_playerId));        
    memcpy(buf+sizeof(inputsPacket)+sizeof(_playerId), &thrust, sizeof(thrust));
    memcpy(buf+sizeof(inputsPacket)+sizeof(_playerId)+sizeof(thrust), &rotation, sizeof(rotation));
    memcpy(buf+sizeof(inputsPacket)+sizeof(_playerId)+sizeof(thrust)+sizeof(rotation), &shooting, sizeof(shooting));

    // printf("Client: inputs sending: %d %d %d %d\n", (signed char)buf[0], (bool)buf[1], (signed char)buf[2], buf[3]);
    Send(buf, sizeof(inputsPacket)+sizeof(_playerId)+sizeof(thrust)+sizeof(rotation)+sizeof(shooting));

    // printf("Client: id = %d", _playerId);
		UpdateDrawFrame();
  }
  _players[_playerId].active = 0;
	CloseWindow();
  ClientShutdown();
}
