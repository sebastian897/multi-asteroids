#include "game_player.h"
#include <string.h>

void StoreInputs(char* buf) 
{
    signed char id;
    bool thrust;
    signed char rotation;
    memcpy(&id, buf, 1);        
    memcpy(&thrust, buf+sizeof(id), sizeof(thrust));
    memcpy(&rotation, buf+sizeof(id)+sizeof(thrust), sizeof(rotation));
    _inputs[id].rotation = rotation;
    _inputs[id].thrust = thrust;
    _players[id].active=true;
}