#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "raylib.h"
#include "utils.h"

#include <vector>

cell_coordinates get_cell();

bool element_in_vector(cell_coordinates, std::vector<cell_coordinates>);

#endif