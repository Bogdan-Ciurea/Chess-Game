#ifndef CHESS_H
#define CHESS_H

#include "chess_board.h"
#include "move.h"

#include <vector>

class Chess{
public:
    Chess_board chess_board;
    int currentPayer;
    std::vector<Move> moveHistory;

    Chess();
    bool playerMove();
    bool endGame();
    ~Chess();
};

#endif