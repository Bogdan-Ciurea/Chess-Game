#ifndef UTILS_H
#define UTILS_H

#define dark_cell  Color {163, 119, 84, 255}
#define white_cell Color {243, 235, 215, 255}
#define move_cell  Color {252, 163, 17, 100}

typedef enum {NO_PIECE, WHITES, BLACKS} cell_state_enum;
typedef enum {NONE, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING} piece_type;

struct cell_coordinates{
    int i, j;
};

#endif