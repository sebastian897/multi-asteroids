#pragma once

#include "asteroid.h"
#include "constants.h"

void AddAsteroid(Vector2 position, AsteroidSize size, float speedMod, bool spawn);
void DestroyAsteroid(int index, float angle);
Vector2 GetNextAsteroidPosition(void);
int UpdateAsteroids(void);
void DrawAsteroids(void);
void ResetAsteroids(void);
extern Asteroid _asteroids[ASTEROID_MAX];

