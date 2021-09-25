#include "../include/raylib.h"
#include "../headers/mapHeader.h"
#include "../headers/movementHeader.h"
#include "../headers/piecesHeader.h"

#include <iostream>
#include <cstring>

using namespace std;


int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 800;
    bool isPressed = false;
    bool currentPlayer = true;
    bool onGoingGame = true;

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
        

        if(onGoingGame){

            ClearBackground(RAYWHITE);
            gameBoard.drawBoard(); // Draw the board

            // Pick up piece
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                startCell = getCell();
                if(gameBoard.stateOfCell(startCell.i, startCell.j) == currentPlayer){
                    if(gameBoard.board[(startCell.i)][(startCell.j)].hasPiece){
                        gameBoard.removePiece(startCell.i, startCell.j);
                        isPressed = true;
                        
                        gameBoard.getMoves(startCell.i, startCell.j);
                    }
                }
            }

            // Hold piece
            if(isPressed){
                currentMouseCoord = GetMousePosition();
                gameBoard.tempPiece.draw(int(currentMouseCoord.x) - gameBoard.getCellSize() / 2, 
                    int(currentMouseCoord.y) - gameBoard.getCellSize() / 2, gameBoard.getCellSize());
            }


            // Drop piece
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isPressed){
                finalCell = getCell();
                if(elementInVector(finalCell, gameBoard.possibleMoves)){
                    if(gameBoard.stateOfCell(finalCell.i, finalCell.j) != currentPlayer && gameBoard.stateOfCell(finalCell.i, finalCell.j) != -1){
                        // Play soud killPiece
                        if(!strcmp(gameBoard.board[finalCell.i][finalCell.j].piece.pieceName(), "King")){
                            onGoingGame = false;
                        }
                    }
                    else{
                        // Play sound movePiece
                    }
                    gameBoard.addPiece(finalCell.i, finalCell.j);
                    isPressed = false;
                    gameBoard.possibleMoves.clear();
                    currentPlayer = !currentPlayer;
                }
                else{
                    gameBoard.addPiece(startCell.i, startCell.j);
                    isPressed = false;
                    gameBoard.possibleMoves.clear();
                }
            }
        

            if(!onGoingGame){
                ClearBackground(RAYWHITE);
                gameBoard.drawBoard();
            } 

        }
        else{
            if(!currentPlayer){
                //ClearBackground(RAYWHITE);
                gameBoard.drawBoard();
                DrawText("White has won!", 200, screenHeight / 2, 50 ,WHITE);
                EndDrawing();
                continue;
            }
            else{
                //ClearBackground(RAYWHITE);
                gameBoard.drawBoard();
                DrawText("Black has won!", 200, screenHeight / 2, 50 ,WHITE);
                EndDrawing();
                break;
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    while (!WindowShouldClose()){   // Detect window close button or ESC key
    
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}