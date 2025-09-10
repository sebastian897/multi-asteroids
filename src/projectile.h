#pragma once

#include "raylib.h"

typedef struct Projectile
{
	bool active;

	Vector2 position;
	float rotation;
	float creationTime;
	signed char playerId;
} Projectile;

Projectile CreateProjectile(Vector2 position, float rotation, signed char id);
bool ProjectileUpdate(Projectile* projectile, float frametime, float time);
void ProjectileDraw(Projectile projectile);
