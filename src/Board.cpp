#include "../include/raylib.h"
#include <../headers/mapHeader.h> 

#include<iostream>

Cell::Cell(Color col, CellPosition celPos){
    color = col;
    position = celPos;
}

Cell::Cell(){

}

ChessBoard::ChessBoard(){
    cellNumber = 8;
    darkCell = Color {163, 119, 84, 255};
    whiteCell = Color {243, 235, 215, 255};

    // Make the board

    for(int i = 0; i < cellNumber; i++){
        for(int j = 0; j < cellNumber; j++){
            if((i + j) % 2 == 0)
                board[i][j] = Cell(whiteCell, CellPosition('a' + j, 8 - i));
            else
                board[i][j] = Cell(darkCell, CellPosition('a' + j, 8 - i));
        }
    }
    // We put the pieces on the board
    this->putPieces();
}

void ChessBoard::drawBoard(){

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    cellWidth = screenWidth / cellNumber;  //These variable will tell us
    cellHeight = screenHeight / cellNumber; // the size of a cell
        
    int centerVariableWidth = 0; // These variables will help us 
    int centerVariableHeight = 0; // center the board to middle the window 

    // Will center the board
    if (screenWidth > screenHeight){
        centerVariableWidth = (screenWidth - screenHeight) / 2;
        centerVariableHeight = 0;
        cellWidth = cellHeight;
    }
    else{
        centerVariableHeight = (screenHeight - screenWidth) / 2;
        centerVariableWidth = 0;
        cellHeight = cellWidth;
    }

    // Draw the board
    for(int i = 0; i < cellNumber; i++)
        for(int j = 0; j < cellNumber; j++){
            board[i][j].size = cellHeight;
            board[i][j].startX = j * cellWidth + centerVariableWidth;
            board[i][j].startY = i * cellHeight + centerVariableHeight;

            DrawRectangle(board[i][j].startX, board[i][j].startY, board[i][j].size, board[i][j].size, board[i][j].color);
        }
        
    // Draw the pieces
    for(int i = 0; i < cellNumber; i++)
        for(int j = 0; j < cellNumber; j++)
            if(board[i][j].hasPiece)
                board[i][j].piece.draw(board[i][j].startX, board[i][j].startY, board[i][j].size);

}

// We put all of the pieces on the board
void ChessBoard::putPieces(){
    // Pawns
    for(int i = 0; i < cellNumber; i++){
        this->board[1][i].piece = Pawn(0);
        this->board[1][i].hasPiece = true;

        this->board[6][i].piece = Pawn(1);
        this->board[6][i].hasPiece = true;
    }
    

    // Bishops
    board[0][2].piece = Bishop(0);
    board[0][2].hasPiece = true;
    board[0][5].piece = Bishop(0);
    board[0][5].hasPiece = true;
    board[7][2].piece = Bishop(1);
    board[7][2].hasPiece = true;
    board[7][5].piece = Bishop(1);
    board[7][5].hasPiece = true;

    // Knights
    board[0][1].piece = Knight(0);
    board[0][1].hasPiece = true;
    board[0][6].piece = Knight(0);
    board[0][6].hasPiece = true;
    board[7][1].piece = Knight(1);
    board[7][1].hasPiece = true;
    board[7][6].piece = Knight(1);
    board[7][6].hasPiece = true;

    // Rooks
    board[0][0].piece = Rook(0);
    board[0][0].hasPiece = true;
    board[0][7].piece = Rook(0);
    board[0][7].hasPiece = true;
    board[7][0].piece = Rook(1);
    board[7][0].hasPiece = true;
    board[7][7].piece = Rook(1);
    board[7][7].hasPiece = true;

    // Kings
    board[0][3].piece = King(0);
    board[0][3].hasPiece = true;
    board[7][3].piece = King(1);
    board[7][3].hasPiece = true;

    // Queens
    board[0][4].piece = Queen(0);
    board[0][4].hasPiece = true;
    board[7][4].piece = Queen(1);
    board[7][4].hasPiece = true;
}

// We reset the board
void ChessBoard::resetBoard(){
    // We check all of the cells to see if they have a piece on it and we eliminate it
    for(int i = 0; i < cellNumber; i++)
        for(int j = 0 ; j < cellNumber; j++)
            try{
                board[i][j].piece.~Piece();
                board[i][j].hasPiece = false;
            }
            catch(const std::exception& e){
            }
    
    this->putPieces();
}

int ChessBoard::stateOfCell(int i, int j){
    if(board[i][j].hasPiece){
        if(board[i][j].piece.teamOfPiece())
            return 1;
        else
            return 0;
    }
    else{
        return -1;
    }
}

int ** ChessBoard::convertBoard(){
    int boardCopy[8][8];
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            boardCopy[i][j] = this->stateOfCell(i, j);
    return boardCopy;
}


void ChessBoard::addPiece(int i, int j){
    board[i][j].piece = tempPiece;
    board[i][j].hasPiece = true;
    tempPiece.~Piece();
}

void ChessBoard::removePiece(int i, int j){
    tempPiece = board[i][j].piece;
    board[i][j].piece.~Piece();
    board[i][j].hasPiece = false;
}

int ChessBoard::getCellSize(){
    return this->cellWidth;
}

ChessBoard::~ChessBoard(){
    
}
