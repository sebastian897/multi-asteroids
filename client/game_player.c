#include "game_player.h"
#include "game_asteroids.h"

Player _players[PLAYERS_MAX] = {0};
Texture2D _texturePlayer;

void InitPlayers(void){
	_texturePlayer = LoadTexture("resources/ship.png");

	ResetPlayers();
}

void ResetPlayers(void)
{
	for(int i = 0; i < PLAYERS_MAX; i++){
		ResetPlayer(&_players[i]);
	}
}

void ResetPlayer(Player* player)
{
	player->position = SCREEN_CENTER;
	player->velocity = (Vector2){0};
	player->rotation = 0;
	player->lastFireTime = -1.0f;
	player->state = PLAYER_DEFAULT;
	player->health = PLAYER_HEALTH_MAX;
	player->active = false;
}

void DrawPlayers(void)
{
	for(int i = 0; i < PLAYERS_MAX; i++){
		if (!_players[i].active) continue;
		PlayerDraw(&_players[i], _texturePlayer);
	}
}

void UpdatePlayers(void){
	for(int i = 0; i < PLAYERS_MAX; i++){
		if (!_players[i].active){continue;}

		TickState(&_players[i]);
		// PlayerMove(&_players[i], i, 0, 0);

		if (_players[i].state == PLAYER_STUNNED)
		{
			return;
		}
		
		// float time = GetTime();
		// if (IsKeyDown(KEY_SPACE))
		// {
		// 	if (time > _players[i].lastFireTime + PLAYER_FIRE_DELAY)
		// 	{
		// 		AddProjectile(Vector2Add(_players[i].position, Vector2Scale(PlayerFacingDirection(_players[i]), PLAYER_PROJECTILE_OFFSET)), _players[i].rotation);
		// 		_players[i].lastFireTime = time;
		// 	}
		// }

		if (_players[i].state == PLAYER_IFRAME)
		{
			return;
		}

		Asteroid* asteroids = _asteroids;

		for (int j = 0; j < ASTEROID_MAX; j++)
		{
			Asteroid* asteroid = asteroids + j;

			if (!asteroid->active)
			{
				continue;
			}

			if (!CheckCollisionCircles(_players[i].position, PLAYER_RADIUS,
				asteroid->position, AsteroidRadius(*asteroid)))
			{
				continue;
			}

			OnCollision(&_players[i], asteroid);
			break;
		}
	}
}
