#include "game_player.h"
#include <string.h>

void StoreInputs(char* buf) 
{
    signed char id;
    bool thrust;
    bool shooting;
    signed char rotation;
    memcpy(&id, buf, 1);        
    memcpy(&thrust, buf+sizeof(id), sizeof(thrust));
    memcpy(&rotation, buf+sizeof(id)+sizeof(thrust), sizeof(rotation));
    memcpy(&shooting, buf+sizeof(id)+sizeof(thrust)+sizeof(rotation), sizeof(shooting));
    _inputs[id].rotation = rotation;
    _inputs[id].thrust = thrust;
    _inputs[id].shooting = shooting;
    _players[id].active=true;
}