#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "raylib.h"
#include "pieces.h" 
#include "cell_position.h"
#include "cell.h"
#include "move.h"
#include "utils.h"

#include <vector>

class Chess_board{
private:
    int cell_number;
    int screen_width, screen_height;
    int cell_width, cell_height;

    std::vector<cell_coordinates> pown_moves  (int i, int j);
    std::vector<cell_coordinates> bishop_moves(int i, int j);
    std::vector<cell_coordinates> knight_moves(int i, int j);
    std::vector<cell_coordinates> rook_moves  (int i, int j);
    std::vector<cell_coordinates> queen_moves (int i, int j);
    std::vector<cell_coordinates> king_moves  (int i, int j);

public:
    Cell board[8][8];
    Piece temp_piece;
    std::vector<cell_coordinates> possible_moves;

    Chess_board();
    ~Chess_board();

    void draw_board();
    void put_pieces();
    void reset_board();

    void add_piece(int i, int j);
    void remove_piece(int i, int j);

    void get_moves(int i, int j);
    cell_state_enum state_of_cell(int i, int j);

    int get_cell_size();
};

#endif