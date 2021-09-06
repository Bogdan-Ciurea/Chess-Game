#include "../include/raylib.h"
#include "../headers/mapHeader.h"
#include "../headers/movementHeader.h"

#include <iostream>
#include <cstring>


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
    moveCell = Color {252, 163, 17, 100};
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
    this->resetBoard();
}

ChessBoard::~ChessBoard(){

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
    for(int i = 0; i < cellNumber; i++){
        for(int j = 0; j < cellNumber; j++){
            board[i][j].size = cellHeight;
            board[i][j].startX = j * cellWidth + centerVariableWidth;
            board[i][j].startY = i * cellHeight + centerVariableHeight;
            //if(elementInVector(cellCoordinates{i,j}, possibleMoves))
                //DrawRectangle(board[possibleMoves[i].i][possibleMoves[i].j].startX, board[possibleMoves[i].i][possibleMoves[i].j].startY, 
                    //board[possibleMoves[i].i][possibleMoves[i].j].size, board[possibleMoves[i].i][possibleMoves[i].j].size, moveCell);
            //else
                DrawRectangle(board[i][j].startX, board[i][j].startY, board[i][j].size, board[i][j].size, board[i][j].color);
        }
    }

    if(!possibleMoves.empty())
        for(int i = 0; i < possibleMoves.size(); i++)
            DrawRectangle(board[possibleMoves[i].i][possibleMoves[i].j].startX, board[possibleMoves[i].i][possibleMoves[i].j].startY, 
                board[possibleMoves[i].i][possibleMoves[i].j].size, board[possibleMoves[i].i][possibleMoves[i].j].size, moveCell);
    

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

    // Queens
    board[0][3].piece = Queen(0);
    board[0][3].hasPiece = true;
    board[7][3].piece = Queen(1);
    board[7][3].hasPiece = true;

    // Kings
    board[0][4].piece = King(0);
    board[0][4].hasPiece = true;
    board[7][4].piece = King(1);
    board[7][4].hasPiece = true;

    //showMapCLI();
}

// We reset the board
void ChessBoard::resetBoard(){
    // We check all of the cells to see if they have a piece on it and we eliminate it
    for(int i = 2; i < 6; i++){
        for(int j = 0 ; j < 8; j++){
            board[i][j].hasPiece = false;
            try{
                board[i][j].piece.~Piece();
            }
            catch(const std::exception& e){
            }
        }
    }
    //showMapCLI();
    this->putPieces();
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


void ChessBoard::getMoves(int i, int j){
    if(!strcmp(this->tempPiece.pieceName(), "Pawn")){
        this->possibleMoves = this->pownMoves(i, j);
    }
    else if(!strcmp(this->tempPiece.pieceName(), "Bishop")){
        this->possibleMoves = this->bishopMoves(i, j);
    }
    else if(!strcmp(this->tempPiece.pieceName(), "Knight")){
        this->possibleMoves = this->knightMoves(i, j);
    }
    else if(!strcmp(this->tempPiece.pieceName(), "Rook")){
        this->possibleMoves = this->rookMoves(i, j);
    }
    else if(!strcmp(this->tempPiece.pieceName(), "Queen")){
        this->possibleMoves = this->queenMoves(i, j);
    }
    else if(!strcmp(this->tempPiece.pieceName(), "King")){
        this->possibleMoves = this->kingMoves(i, j);
    }
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


int ChessBoard::getCellSize(){
    return this->cellWidth;
}

void ChessBoard::showMapCLI(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout<<this->stateOfCell(i,j)<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n\n";
}


std::vector<cellCoordinates> ChessBoard::pownMoves(int i, int j){
    std::vector<cellCoordinates> list;
    if(this->tempPiece.teamOfPiece()){
        // Move on empty cells
        if(i == 6){
            if(stateOfCell(i - 1, j) == -1){
                list.push_back(cellCoordinates{i - 1, j});
                if(stateOfCell(i - 2, j) == -1)
                    list.push_back(cellCoordinates{i - 2, j});
            }
        }
        else{
            if(i > 0 && stateOfCell(i - 1, j) == -1)
                list.push_back(cellCoordinates{i - 1, j});
        }
        // Atack other pieces
        if(i > 0 && j > 0 && stateOfCell(i - 1, j - 1) == 0)
            list.push_back(cellCoordinates{i - 1, j - 1});
        if(i > 0 && j < 7 && stateOfCell(i - 1, j + 1) == 0)
            list.push_back(cellCoordinates{i - 1, j + 1});

        // TODO: Make the en percent move
    }
    // Move the black pawns
    else{
        // Move on empty cells
        if(i == 1){
            if(stateOfCell(i + 1, j) == -1){
                list.push_back(cellCoordinates{i + 1, j});
                if(stateOfCell(i + 2, j) == -1)
                    list.push_back(cellCoordinates{i + 2, j});
            }
        }
        else{
            if(i < 7 && stateOfCell(i + 1, j) == -1)
                list.push_back(cellCoordinates{i + 1, j});
        }

        // Atack other pieces
        if(i < 7 && j > 0 && stateOfCell(i + 1, j - 1) == 1)
            list.push_back(cellCoordinates{i + 1, j - 1});
        if(i < 7 && j < 7 && stateOfCell(i + 1, j + 1) == 1)
            list.push_back(cellCoordinates{i + 1, j + 1});

        // TODO: Make the en percent move
    }

    return list;
}

std::vector<cellCoordinates> ChessBoard::bishopMoves(int i, int j){
    std::vector<cellCoordinates> list;

    // Go Bottom Right
    int currentI = i, currentJ = j;
    while(true){
        if(currentI < 7 && currentJ < 7){
            currentI++;
            currentJ++;
        }
        else
            break; 

        if(stateOfCell(currentI, currentJ) == -1)
            list.push_back(cellCoordinates{currentI, currentJ});
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;    
    }

    // Go Bottom Left
    currentI = i, currentJ = j;
    while(true){
        if(currentI < 7 && currentJ > 0){
            currentI++;
            currentJ--;
        }
        else
            break; 

        if(stateOfCell(currentI, currentJ) == -1)
            list.push_back(cellCoordinates{currentI, currentJ});
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    // Go Top Right
    currentI = i, currentJ = j;
    while(true){
        if(currentI > 0 && currentJ < 7){
            currentI--;
            currentJ++;
        }
        else
            break; 

        if(stateOfCell(currentI, currentJ) == -1)
            list.push_back(cellCoordinates{currentI, currentJ});
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    // Go Top Left
    currentI = i, currentJ = j;
    while(true){
        if(currentI > 0 && currentJ > 0){
            currentI--;
            currentJ--;
        }
        else
            break; 

        if(stateOfCell(currentI, currentJ) == -1)
            list.push_back(cellCoordinates{currentI, currentJ});
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    return list;
}

std::vector<cellCoordinates> ChessBoard::knightMoves(int i, int j){
    std::vector<cellCoordinates> list;

    if(i - 1 >= 0 && j - 2 >= 0 && tempPiece.teamOfPiece() != stateOfCell(i - 1, j - 2))
        list.push_back(cellCoordinates{i - 1, j - 2});

    if(i - 2 >= 0 && j - 1 >= 0 && tempPiece.teamOfPiece() != stateOfCell(i - 2, j - 1))
        list.push_back(cellCoordinates{i - 2, j - 1});

    if(i - 2 >= 0 && j + 1 <= 7 && tempPiece.teamOfPiece() != stateOfCell(i - 2, j + 1))
        list.push_back(cellCoordinates{i - 2, j + 1});

    if(i - 1 >= 0 && j + 2 <= 7 && tempPiece.teamOfPiece() != stateOfCell(i - 1, j + 2))
        list.push_back(cellCoordinates{i - 1, j + 2});


    if(i + 1 <= 7 && j - 2 >= 0 && tempPiece.teamOfPiece() != stateOfCell(i + 1, j - 2))
        list.push_back(cellCoordinates{i + 1, j - 2});
    
    if(i + 2 <= 7 && j - 1 >= 0 && tempPiece.teamOfPiece() != stateOfCell(i + 2, j - 1))
        list.push_back(cellCoordinates{i + 2, j - 1});

    if(i + 2 <= 7 && j + 1 <= 7 && tempPiece.teamOfPiece() != stateOfCell(i + 2, j + 1))
        list.push_back(cellCoordinates{i + 2, j + 1});

    if(i + 1 <= 7 && j + 2 <= 7 && tempPiece.teamOfPiece() != stateOfCell(i + 1, j + 2))
        list.push_back(cellCoordinates{i + 1, j + 2});

    return list;
}

std::vector<cellCoordinates> ChessBoard::rookMoves(int i, int j){
    std::vector<cellCoordinates> list;

    int currentI = i, currentJ = j;

    // Go Right
    while(true){
        if(currentJ < 7)
            currentJ++;
        else
            break;

        if(stateOfCell(currentI, currentJ) == -1){
            list.push_back(cellCoordinates{currentI, currentJ});
        }
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    currentJ = j;
    // Go Left
    while(true){
        if(currentJ > 0)
            currentJ--;
        else
            break;

        if(stateOfCell(currentI, currentJ) == -1){
            list.push_back(cellCoordinates{currentI, currentJ});
        }
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    currentJ = j;
    // Go Up
    while(true){
        if(currentI > 0)
            currentI--;
        else
            break;

        if(stateOfCell(currentI, currentJ) == -1){
            list.push_back(cellCoordinates{currentI, currentJ});
        }
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }

    currentI = i;
    // Go Down
    while(true){
        if(currentI < 7)
            currentI++;
        else
            break;

        if(stateOfCell(currentI, currentJ) == -1){
            list.push_back(cellCoordinates{currentI, currentJ});
        }
        else if(tempPiece.teamOfPiece() != stateOfCell(currentI, currentJ)){
            list.push_back(cellCoordinates{currentI, currentJ});
            break;
        }
        else
            break;
    }
    
    return list;
}

std::vector<cellCoordinates> ChessBoard::queenMoves(int i, int j){
    std::vector<cellCoordinates> list = this->bishopMoves(i, j);
    std::vector<cellCoordinates> list2 = this->rookMoves(i, j);

    for(int i = 0; i < list2.size(); i++)
        list.push_back(list2[i]);

    return list;
}

std::vector<cellCoordinates> ChessBoard::kingMoves(int i, int j){
    std::vector<cellCoordinates> list;

    for(int m = -1; m <= 1; m++)
        for(int n = -1; n <= 1; n++)
            if(m || n)
                if(m + i < 8 && m + i >= 0 && n + j < 8 && n + j >= 0 && tempPiece.teamOfPiece() != stateOfCell(m + i, n + j))
                    list.push_back(cellCoordinates{m + i, n + j});

    // Casteling
    if((i == 0 || i == 7) && j == 4 ){
        if(!this->board[i][j+1].hasPiece && !this->board[i][j+2].hasPiece && this->board[i][j+3].hasPiece){
            if(!strcmp(this->board[i][j+3].piece.pieceName(), "Rook"))
                list.push_back(cellCoordinates{i, j + 2});
        }
        if(!this->board[i][j-1].hasPiece && !this->board[i][j-2].hasPiece && !this->board[i][j-3].hasPiece && this->board[i][j-4].hasPiece){
            if(!strcmp(this->board[i][j+3].piece.pieceName(), "Rook"))
                list.push_back(cellCoordinates{i, j - 2});
        }
    }

    //TODO: Move the Rook if there is a Casteling move
    //TODO: The king cannot move into a dangerous posotion

    return list;
}
