#include "raylib.h"
#include "../include/chess_board.h"

using namespace std;

int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    int  screen_width  = 800;
    int  screen_height = 800;
    bool is_pressed    = false;
    bool on_going_game = true;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "Chess");

    cell_state_enum  current_player = WHITES;
    Chess_board      game_board = Chess_board();
    cell_coordinates start_cell = {0}; 
    cell_coordinates final_cell = {0};

    Vector2 current_mouse_coords;

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
        

        if (on_going_game) {

            ClearBackground(RAYWHITE);
            game_board.draw_board(); // Draw the board

            // Pick up piece
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                start_cell = get_cell();
                if (game_board.state_of_cell(start_cell.i, start_cell.j) == current_player) {
                    if (game_board.board[(start_cell.i)][(start_cell.j)].has_piece) {
                        game_board.remove_piece(start_cell.i, start_cell.j);
                        is_pressed = true;
                        game_board.get_moves(start_cell.i, start_cell.j);
                    }
                }
            }

            // Hold piece
            if (is_pressed) {
                current_mouse_coords = GetMousePosition();
                game_board.temp_piece.draw(int(current_mouse_coords.x) - game_board.get_cell_size() / 2,
                                           int(current_mouse_coords.y) - game_board.get_cell_size() / 2,
                                           game_board.get_cell_size());
            }


            // Drop piece
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && is_pressed) {
                final_cell = get_cell();
                if (element_in_vector(final_cell, game_board.possible_moves)) {
                    if (game_board.state_of_cell(final_cell.i, final_cell.j) != current_player
                       && game_board.state_of_cell(final_cell.i, final_cell.j) != NO_PIECE) {
                        // Play soud killPiece
                        if (game_board.board[final_cell.i][final_cell.j].piece.get_piece_type() == KING) {
                            on_going_game = false;
                        }
                    }
                    else {
                        // Play sound movePiece
                    }
                    game_board.add_piece(final_cell.i, final_cell.j);
                    is_pressed = false;
                    game_board.possible_moves.clear();
                    if (current_player == WHITES) {
                        current_player = BLACKS;
                    }
                    else {
                        current_player = WHITES;
                    }
                }
                else {
                    game_board.add_piece(start_cell.i, start_cell.j);
                    is_pressed = false;
                    game_board.possible_moves.clear();
                }
            }
        

            if (!on_going_game) {
                ClearBackground(RAYWHITE);
                game_board.draw_board();
            } 

        }
        else {
            if (!current_player) {
                //ClearBackground(RAYWHITE);
                game_board.draw_board();
                DrawText("White has won!", 200, screen_height / 2, 50 ,WHITE);
                EndDrawing();
                break;
            }
            else {
                //ClearBackground(RAYWHITE);
                game_board.draw_board();
                DrawText("Black has won!", 200, screen_height / 2, 50 ,WHITE);
                EndDrawing();
                break;
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}