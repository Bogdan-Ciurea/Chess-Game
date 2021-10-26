#ifndef CELL_H
#define CELL_H

#include "raylib.h"
#include "pieces.h"
#include "cell_position.h"

class Cell{
public:
    int startX, startY, size;
    bool has_piece;

    Cell();
    Cell(Color, Cell_position);
    Color color;
    Piece piece;
    Cell_position position;
    ~Cell();
};

#endif