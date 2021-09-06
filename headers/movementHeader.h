#ifndef movementHeader
#define movementHeader

#include "../include/raylib.h"
#include <vector>

struct cellCoordinates{
    int i, j;
};

cellCoordinates getCell();

bool elementInVector(cellCoordinates, std::vector<cellCoordinates>);

#endif