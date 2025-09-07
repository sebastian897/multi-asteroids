#include "netif.h"
#include <stdio.h>

// bool active;

// 	Vector2 position;
// 	Vector2 velocity;
// 	AsteroidSize size;

// 	float rotation;
// 	float rotationSpeed;
// 	float creationTime;

void PrintAsteroid(const Asteroid* asteroid) {
    if (!asteroid->active){
        printf("empty");
        return;
    }
    printf("ast: x = %f y = %f\n", asteroid->position.x,asteroid->position.y);
    printf("ast: vx = %f vy = %f\n", asteroid->velocity.x,asteroid->velocity.y);
    printf("ast: size = %d\n", asteroid->size);
    printf("ast: r = %f rs = %f\n", asteroid->rotation,asteroid->rotationSpeed);
    printf("ast: ct = %f\n", asteroid->creationTime);
}

