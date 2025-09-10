#pragma once

#include "raylib.h"
#include "asteroid.h"

#define PLAYER_RADIUS 24

typedef enum PlayerState
{
	PLAYER_DEFAULT = 0,
	PLAYER_STUNNED,
	PLAYER_IFRAME,
	PLAYER_DEAD
} PlayerState;

typedef struct Player
{
	Vector2 position;
	Vector2 velocity;
	PlayerState state;
	float timeStateEntered;
	float rotation;
	float lastFireTime;
	int health;
	bool active;
} Player;

typedef enum Thrust :bool
{
	THRUST_NONE=0,
	THRUST_FORWARD=1
} Thrust;

typedef enum Shooting :bool
{
	SHOOT_NONE=0,
	SHOOT_BULLET=1
} Shooting;

typedef enum Rotation :signed char
{
	ROTATION_NONE=0,
	ROTATION_CW=1,
	ROTATION_CCW=-1
} Rotation;


typedef struct PlayerInputs
{
	Thrust thrust;
	Rotation rotation;
	Shooting shooting;
} PlayerInputs;



void PlayerMove(Player* player, bool thrust, signed char rotvel);
void PlayerDraw(Player* player, Texture2D texture);
Vector2 PlayerFacingDirection(Player player);
void PlayerSetState(Player* player, PlayerState state);
void OnCollision(Player* player, Asteroid* asteroid);
