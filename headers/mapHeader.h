#ifndef mapHeader
#define mapHeader

#include "../include/raylib.h"
#include "piecesHeader.h" 
#include <vector>

class Cell{
public:
    int startX, startY, size;
    bool hasPiece;

    Cell();
    Cell(Color, CellPosition);
    Color color;
    Piece piece;
    CellPosition position;
};

class Move{
public:
    Piece piece;
    Piece killedPiece;
    CellPosition startPosition;
    CellPosition endPosition;
};

class ChessBoard{
private:
    int cellNumber;
    int screenWidth, screenHeight;
    int cellWidth, cellHeight;

    Color darkCell;
    Color whiteCell;

public:
    Cell board[8][8];
    Piece tempPiece;

    ChessBoard();
    void putPieces();
    void addPiece(int i, int j);
    void removePiece(int i, int j);
    int stateOfCell(int i, int j);
    void drawBoard();
    int **convertBoard();
    int getCellSize();
    void resetBoard();
    void updateBoard(Move move);
    ~ChessBoard();
};

class Chess{
public:
    ChessBoard chessBoard;
    int currentPayer;
    std::vector<Move> moveHistory;

    Chess();
    bool playerMove();
    bool endGame();
    ~Chess();
};

#endif