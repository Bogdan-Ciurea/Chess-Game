#include "include/raylib.h"
#include "headers/mapHeader.h"
#include "headers/movementHeader.h"
#include "headers/piecesHeader.h"

#include <iostream>
using namespace std;


int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 800;
    bool isPressed = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Chess");

    ChessBoard gameBoard = ChessBoard();
    cellCoordinates startCell, finalCell;

    Vector2 currentMouseCoord;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        gameBoard.drawBoard(); // Draw the board

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            startCell = getCell();
            if(gameBoard.board[(startCell.i)][(startCell.j)].hasPiece){
                gameBoard.removePiece(startCell.i, startCell.j);
                isPressed = true;
                
                gameBoard.getMoves(startCell.i, startCell.j);
            }
        }

        if(isPressed){
            currentMouseCoord = GetMousePosition();
            gameBoard.tempPiece.draw(int(currentMouseCoord.x) - gameBoard.getCellSize() / 2, 
                int(currentMouseCoord.y) - gameBoard.getCellSize() / 2, gameBoard.getCellSize());
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isPressed){
            finalCell = getCell();
            if(elementInVector(finalCell, gameBoard.possibleMoves)){
                gameBoard.addPiece(finalCell.i, finalCell.j);
                isPressed = false;
                gameBoard.possibleMoves.clear();
            }
            else{
                gameBoard.addPiece(startCell.i, startCell.j);
                isPressed = false;
                gameBoard.possibleMoves.clear();
            }
        }

        //TODO: Daca apas pe o patratica goala, apare o piesa

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}