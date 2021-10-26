#ifndef MOVE_H
#define MOVE_H

#include "pieces.h"
#include "cell_position.h"

class Move{
public:
    Piece piece;
    Piece killed_piece;
    Cell_position start_position;
    Cell_position end_position;
};

#endif