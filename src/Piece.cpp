#include <../headers/piecesHeader.h>
#include <../headers/mapHeader.h>

using namespace std;
#include <iostream>

//0 pawn | 1 bishop | 2 knight | 3 rook | 4 queen | 5 king

CellPosition::CellPosition(char chr, int j){
    this->ch = chr;
    this->i = j;
}

CellPosition::CellPosition(){
    
}


Piece::Piece(){

}

void Piece::draw(int x, int y, int size){
    DrawTextureEx(texture, Vector2{float(x),float(y)}, 0, float(size) / 500, WHITE);
}

char * Piece::pieceName(){
    return this->name;
}

vector<cellCoordinates>Piece::possibleMoves(cellCoordinates fromPosition, int ** gameBoardCopy){
    vector<cellCoordinates> list;
    return list;
}

bool Piece::teamOfPiece(){
    return this->teamPiece;
}

Piece::~Piece(){
    
}


Pawn::Pawn(int team){
    teamPiece = team;
    name = "Pawn";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        this->img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-pawn-white.png");
    else
        this->img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-pawn-black.png");
    
    this->texture = LoadTextureFromImage(this->img);
    UnloadImage(this->img);  
}

vector<cellCoordinates>Pawn::possibleMoves(cellCoordinates fromPosition, int ** gameBoardCopy){
    vector<cellCoordinates> list;
    
    //Move the white pawns
    if(teamPiece){
        // Move on empty cells
        if(fromPosition.i == 6){
            if(gameBoardCopy[fromPosition.i - 1][fromPosition.j] == -1){
                list.push_back(cellCoordinates{fromPosition.i - 1, fromPosition.j});
                if(gameBoardCopy[fromPosition.i - 2][fromPosition.j] == -1)
                    list.push_back(cellCoordinates{fromPosition.i - 2, fromPosition.j});
            }
        }
        else{
            if(fromPosition.i > 0 && gameBoardCopy[fromPosition.i - 1][fromPosition.j] == -1)
                list.push_back(cellCoordinates{fromPosition.i - 1, fromPosition.j});
        }
        // Atack other pieces
        if(fromPosition.i > 0 && fromPosition.j > 0 && gameBoardCopy[fromPosition.i - 1][fromPosition.j - 1] == 0)
            list.push_back(cellCoordinates{fromPosition.i - 1, fromPosition.j - 1});
        if(fromPosition.i > 0 && fromPosition.j < 7 && gameBoardCopy[fromPosition.i - 1][fromPosition.j + 1] == 0)
            list.push_back(cellCoordinates{fromPosition.i - 1, fromPosition.j + 1});

        // TODO: Make the en percent move
    }
    // Move the black pawns
    else{
        // Move on empty cells
        if(fromPosition.i == 1){
            if(gameBoardCopy[fromPosition.i + 1][fromPosition.j] == -1){
                list.push_back(cellCoordinates{fromPosition.i + 1, fromPosition.j});
                if(gameBoardCopy[fromPosition.i + 2][fromPosition.j] == -1)
                    list.push_back(cellCoordinates{fromPosition.i + 2, fromPosition.j});
            }
        }
        else{
            if(fromPosition.i < 7 && gameBoardCopy[fromPosition.i + 1][fromPosition.j] == -1)
                list.push_back(cellCoordinates{fromPosition.i + 1, fromPosition.j});
        }

        // Atack other pieces
        if(fromPosition.i < 7 && fromPosition.j > 0 && gameBoardCopy[fromPosition.i + 1][fromPosition.j - 1] == 0)
            list.push_back(cellCoordinates{fromPosition.i + 1, fromPosition.j - 1});
        if(fromPosition.i < 7 && fromPosition.j < 7 && gameBoardCopy[fromPosition.i + 1][fromPosition.j + 1] == 0)
            list.push_back(cellCoordinates{fromPosition.i + 1, fromPosition.j + 1});

        // TODO: Make the en percent move
    }

    return list;
}

Pawn::~Pawn(){
}


Bishop::Bishop(int team){
    teamPiece = team;
    name = "Bishop";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-bishop-white.png");
    else
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-bishop-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Bishop::~Bishop(){
}


Knight::Knight(int team){
    teamPiece = team;
    name = "Knight";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-knight-white.png");
    else
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-knight-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Knight::~Knight(){
}


Rook::Rook(int team){
    teamPiece = team;
    name = "Rook";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-rook-white.png");
    else
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-rook-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Rook::~Rook(){
}


Queen::Queen(int team){
    teamPiece = team;
    name = "Queen";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-queen-white.png");
    else
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-queen-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Queen::~Queen(){
}


King::King(int team){
    teamPiece = team;
    name = "King";
    
    if(team) // Whites coresponds to 1 and Blacks coresponds to 0
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-king-white.png");
    else
        img = LoadImage("C:/Users/ciure/Desktop/Things/C++/Game/assets/chess-king-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

King::~King(){
}
