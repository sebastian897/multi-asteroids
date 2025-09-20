#include "player.h"
#include "asteroid.h"
#include "raymath.h"
#include "debug.h"
#include "constants.h"
#include <stdio.h>

#define PLAYER_ROT_SPEED 360
#define PLAYER_SPEED 250
#define PLAYER_ACCELERATION 750
#define PLAYER_DECELERATION 175
#define PLAYER_NUDGE_VELOCITY 150

#define FIELD_MIN_X (-PLAYER_RADIUS / 2)
#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS / 2)
#define FIELD_MIN_Y (-PLAYER_RADIUS / 2)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS / 2)

static void UpdateAngle(Player* player, float frametime, signed char rotvel)
{
	// if (_playerId==id){
	// int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT); use for client
	// int xIn = (int)rotclk - (int)rotant;

	player->rotation += (rotvel * PLAYER_ROT_SPEED * frametime);
	// }
}

static void UpdateVelocity(Player* player, float frametime, bool thrust)
{
	float magSqr = Vector2LengthSqr(player->velocity);
	float mag = sqrt(magSqr);
	Vector2 facingDirection = PlayerFacingDirection(*player);

	// int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);

	if (thrust){
		player->velocity = Vector2Add(player->velocity,
			Vector2Scale(facingDirection, PLAYER_ACCELERATION * frametime));
		if (mag > PLAYER_SPEED)
		{
			player->velocity = Vector2Scale(player->velocity, PLAYER_SPEED / mag);
		}
	}
	else
	{
		if (mag > 0)
		{
			float xSign = (player->velocity.x < 0) ? -1.0f: 1.0f;
			float ySign = (player->velocity.y < 0) ? -1.0f: 1.0f;

			float xAbs = player->velocity.x * xSign;
			float yAbs = player->velocity.y * ySign;

			float xWeight = xAbs * xAbs / magSqr;
			float yWeight = yAbs * yAbs / magSqr;

			float xDecel = xWeight * PLAYER_DECELERATION * xSign * frametime;
			float yDecel = yWeight * PLAYER_DECELERATION * ySign * frametime;

			player->velocity.x = (xAbs > xDecel) ? player->velocity.x - xDecel : 0;
			player->velocity.y = (yAbs > yDecel) ? player->velocity.y - yDecel : 0;
		}
	}

	return;
}

static void UpdateWrap(Player* player, float frametime)
{
	if (player->position.x > FIELD_MAX_X)
	{
		player->position.x = FIELD_MIN_X;

		if (player->velocity.x < PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.x = PLAYER_NUDGE_VELOCITY;
		}
	}
	else if (player->position.x < FIELD_MIN_X)
	{
		player->position.x = FIELD_MAX_X;

		if (player->velocity.x > -PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.x = -PLAYER_NUDGE_VELOCITY;
		}
	}
	
	if (player->position.y > FIELD_MAX_Y)
	{
		player->position.y = FIELD_MIN_Y;

		if (player->velocity.y < PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.y = PLAYER_NUDGE_VELOCITY;
		}
	}
	else if (player->position.y < FIELD_MIN_Y)
	{
		player->position.y = FIELD_MAX_Y;

		if (player->velocity.y > -PLAYER_NUDGE_VELOCITY)
		{
			player->velocity.y = -PLAYER_NUDGE_VELOCITY;
		}
	}
}

void PlayerMove(Player* player, bool thrust, signed char rotvel)
{

	printf("Server: inputs recieved: %d %d\n", thrust, rotvel);

	float frametime = GetFrameTime();

	if (player->state != PLAYER_STUNNED && player->state != PLAYER_DEAD)
	{
		UpdateAngle(player, frametime, rotvel);
		UpdateVelocity(player, frametime, thrust);
	}

	player->position = Vector2Add(player->position, Vector2Scale(player->velocity, frametime));
	UpdateWrap(player, frametime);

	SetPlayerInfo(player->position, player->velocity, player->rotation);
}

static void OnDeath(Player* player)
{
	PlayerSetState(player, PLAYER_DEAD);
}

void OnCollision(Player* player, Asteroid* asteroid)
{
	const float playerNudgeMagnitude = 200.0f;
	const float asteroidSpeedReduction = 0.4f;

	player->health--;
	if (player->health <= 0)
	{
		OnDeath(player);
		return;
	}

	PlayerSetState(player, PLAYER_STUNNED);

	Vector2 nudgeDirection = Vector2Normalize(Vector2Subtract(player->position, asteroid->position));
	player->velocity = Vector2Scale(nudgeDirection, playerNudgeMagnitude);

	asteroid->velocity = Vector2Scale(asteroid->velocity, asteroidSpeedReduction);
}

void TickState(Player* player)
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

void PlayerDraw(Player* player, Texture2D texture)
{

	if (player->state == PLAYER_DEAD)
	{
		return;
	}

	const Rectangle source = {0, 0, 32, 32};
	Rectangle dest = {player->position.x, player->position.y, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
	Vector2 origin = {dest.width / 2, dest.height / 2};

	Color color = WHITE;
	if (player->state == PLAYER_IFRAME)
	{
		float seconds = GetTime() - player->timeStateEntered;
		int value = (int)(seconds * 6.0f);
		if (value % 2)
		{
			color = Fade(RED, 0.6f);
		}
	}

	DrawTexturePro(texture, source, dest, origin, player->rotation, color);
}

Vector2 PlayerFacingDirection(Player player)
{
	return Vector2Rotate((Vector2){0, -1}, player.rotation * DEG2RAD);
}

void PlayerSetState(Player* player, PlayerState state)
{
	player->state = state;
	player->timeStateEntered = GetTime();
}
