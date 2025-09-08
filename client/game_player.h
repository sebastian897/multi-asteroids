#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "player.h"
#include "constants.h"

#define PLAYER_PROJECTILE_OFFSET PLAYER_RADIUS
#define PLAYER_FIRE_DELAY 0.33f
#define PLAYER_HEALTH_MAX 5

void InitPlayers(void);
void DrawPlayers(void);
void UpdatePlayers(void);
void ResetPlayer(Player* player);
void ResetPlayers(void);

extern Player _players[PLAYERS_MAX];

#endif
