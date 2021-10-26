#ifndef PIECES_H
#define PIECES_H

#include "raylib.h"
#include "movement.h"
#include "utils.h"

#include <vector>

using namespace std;

class Piece {
protected:
    cell_state_enum team_piece;
    Image           img;
    Texture2D       texture;
    piece_type      type;
public:
    Piece();
    piece_type get_piece_type();
    cell_state_enum team_of_piece();
    void draw(int x, int y, int size);
    bool move(cell_coordinates from_position, cell_coordinates toPosition);
    bool validate(cell_coordinates from_position, cell_coordinates toPosition);
    ~Piece();
};

class Pawn : public Piece {
public:
    Pawn(cell_state_enum team);
    ~Pawn();
};

class Bishop : public Piece {
public:
    Bishop(cell_state_enum team);
    ~Bishop();
};

class Knight : public Piece {
public:
    Knight(cell_state_enum team);
    ~Knight();
};

class Rook : public Piece {
public:
    Rook(cell_state_enum team);
    ~Rook();
};

class Queen : public Piece {
public:
    Queen(cell_state_enum team);
    ~Queen();
};

class King : public Piece {
public:
    King(cell_state_enum team);
    ~King();
};

#endif