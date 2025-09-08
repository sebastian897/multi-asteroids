#ifndef GAME_PROJECTILES_H_
#define GAME_PROJECTILES_H_

#include "projectile.h"
#include "constants.h"

void AddProjectile(Vector2 position, float rotation, signed char id);
int UpdateProjectiles(void);
void DrawProjectiles(void);
void ResetProjectiles(void);
extern Projectile _projectiles[PROJECTILE_MAX];
#endif
