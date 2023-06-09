#include "raylib.h"
#include "../include/pieces.h"

using namespace std;


Piece::Piece(){

}

void Piece::draw(int x, int y, int size){
    DrawTextureEx(texture, Vector2{float(x),float(y)}, 0, float(size) / 500, WHITE);
}

piece_type Piece::get_piece_type(){
    return this->type;
}


cell_state_enum Piece::team_of_piece(){
    return this->team_piece;
}

Piece::~Piece(){
    
}

Pawn::Pawn(cell_state_enum team){
    this->team_piece = team;
    this->type = PAWN;
    
    if(team == WHITES)
        this->img = LoadImage("assets/chess-pawn-white.png");
    else if (team == BLACKS)
        this->img = LoadImage("assets/chess-pawn-black.png");
    
    this->texture = LoadTextureFromImage(this->img);
    UnloadImage(this->img);  
}

Pawn::~Pawn(){

}

Bishop::Bishop(cell_state_enum team){
    this->team_piece = team;
    this->type = BISHOP;
    
    if (team == WHITES)
        img = LoadImage("assets/chess-bishop-white.png");
    else if (team == BLACKS)
        img = LoadImage("assets/chess-bishop-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Bishop::~Bishop(){
    
}

Knight::Knight(cell_state_enum team){
    this->team_piece = team;
    this->type = KNIGHT;
    
    if (team == WHITES)
        img = LoadImage("assets/chess-knight-white.png");
    else if (team == BLACKS)
        img = LoadImage("assets/chess-knight-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Knight::~Knight(){

}

Rook::Rook(cell_state_enum team){
    this->team_piece = team;
    this->type = ROOK;
    
    if (team == WHITES)
        img = LoadImage("assets/chess-rook-white.png");
    else if (team == BLACKS)
        img = LoadImage("assets/chess-rook-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Rook::~Rook(){

}

Queen::Queen(cell_state_enum team){
    this->team_piece = team;
    this->type = QUEEN;
    
    if (team == WHITES)
        img = LoadImage("assets/chess-queen-white.png");
    else if (team == BLACKS)
        img = LoadImage("assets/chess-queen-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

Queen::~Queen(){

}

King::King(cell_state_enum team){
    this->team_piece = team;
    this->type = KING;
    
    if (team == WHITES)
        img = LoadImage("assets/chess-king-white.png");
    else if (team == BLACKS)
        img = LoadImage("assets/chess-king-black.png");

    texture = LoadTextureFromImage(img);
    UnloadImage(img);  
}

King::~King(){

}
