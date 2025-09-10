#include "game_player.h"
#include "game_asteroids.h"

#include "raymath.h"

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




static void TickState(Player* player)
{
	const float stunDuration = 0.2f;
	const float iframeDuration = 0.8f;
	const float playerDeathDelay = 0.8f;

	switch (player->state)
	{
	case PLAYER_DEFAULT:
		// no check
		break;
		
	case PLAYER_STUNNED:
		if ((GetTime() - player->timeStateEntered) > stunDuration)
		{
			PlayerSetState(player, PLAYER_IFRAME);
		}
		break;
		
	case PLAYER_IFRAME:
		if ((GetTime() - player->timeStateEntered) > iframeDuration)
		{
			PlayerSetState(player, PLAYER_DEFAULT);
		}
		break;
		
	case PLAYER_DEAD:
		if ((GetTime() - player->timeStateEntered) > playerDeathDelay)
		{
			// GameOver(); to do need new game over
		}
		break;

	default:
		TraceLog(LOG_ERROR, "PlayerState %d not handled!", (int)player->state);
		break;
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

		Asteroid* asteroids = AsteroidsArray();
		const int count = ASTEROID_MAX;

		for (int i = 0; i < count; i++)
		{
			Asteroid* asteroid = asteroids + i;

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
