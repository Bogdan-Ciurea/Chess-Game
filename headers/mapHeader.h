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
    Color moveCell;
    
    void showMapCLI(); 

    std::vector<cellCoordinates> pownMoves(int i, int j);
    std::vector<cellCoordinates> bishopMoves(int i, int j);
    std::vector<cellCoordinates> knightMoves(int i, int j);
    std::vector<cellCoordinates> rookMoves(int i, int j);
    std::vector<cellCoordinates> queenMoves(int i, int j);
    std::vector<cellCoordinates> kingMoves(int i, int j);

public:
    Cell board[8][8];
    Piece tempPiece;
    std::vector<cellCoordinates> possibleMoves;

    ChessBoard();
    ~ChessBoard();

    void drawBoard();
    void putPieces();
    void resetBoard();

    void addPiece(int i, int j);
    void removePiece(int i, int j);

    void getMoves(int i, int j);
    int stateOfCell(int i, int j);

    int getCellSize();
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