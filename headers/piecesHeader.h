#ifndef piecesHeader
#define piecesHeader

#include "../include/raylib.h"
#include "movementHeader.h"
#include <vector>

using namespace std;

class CellPosition{
public:
    CellPosition();
    CellPosition(char, int);
    char ch;
    int i;
};

class Piece{
protected:
    int teamPiece;
    Image img;
    Texture2D texture; // This will store the Texture2D of the piece
    char * name;
public:

    Piece();
    char * pieceName();
    bool teamOfPiece();
    void draw(int x, int y, int size);
    bool move(cellCoordinates fromPosition, cellCoordinates toPosition);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition, int ** gameBoardCopy);
    bool validate(cellCoordinates fromPosition, cellCoordinates toPosition);
    ~Piece();
};

class Pawn : public Piece{
public:
    Pawn(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition, int ** gameBoardCopy);
    ~Pawn();
};

class Bishop : public Piece{
public:
    Bishop(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition);
    ~Bishop();
};

class Knight : public Piece{
public:
    Knight(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition);
    ~Knight();
};

class Rook : public Piece{
public:
    Rook(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition);
    ~Rook();
};

class Queen : public Piece{
public:
    Queen(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition);
    ~Queen();
};

class King : public Piece{
public:
    King(int team);
    vector<cellCoordinates> possibleMoves(cellCoordinates fromPosition);
    ~King();
};

#endif