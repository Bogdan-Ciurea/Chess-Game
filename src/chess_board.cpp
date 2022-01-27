#include "../include/chess_board.h"

/**
 * This function will be the constructor for the Chess_board class.
 * 
 */
Chess_board::Chess_board() {
    this->cell_number = 8;

    // Make the board
    for (int i = 0; i < this->cell_number; i++) {
        for (int j = 0; j < this->cell_number; j++) {
            if ((i + j) % 2 == 0) {
                this->board[i][j] = Cell(white_cell, Cell_position('a' + j, 8 - i));
            }
            else {
                this->board[i][j] = Cell(dark_cell, Cell_position('a' + j, 8 - i));
            }
        }
    }
    // We put the pieces on the board
    this->reset_board();
}

/**
 * This function will be the deconstructor for the Chess_board class.
 * 
 */
Chess_board::~Chess_board(){

}

/**
 * This function will draw the board.
 * 
 */
void Chess_board::draw_board() {

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    // These variable will tell us the size of a cell
    cell_width = screen_width / cell_number;
    cell_height = screen_height / cell_number;
    
    // These variables will help us center the board to middle of the window
    int center_variable_width = 0;
    int center_variable_height = 0;

    // Will center the board
    if (screen_width > screen_height) {
        center_variable_width = (screen_width - screen_height) / 2;
        center_variable_height = 0;
        cell_width = cell_height;
    }
    else {
        center_variable_height = (screen_height - screen_width) / 2;
        center_variable_width = 0;
        cell_height = cell_width;
    }

    // Draw the board
    for (int i = 0; i < cell_number; i++) {
        for (int j = 0; j < cell_number; j++) {
            board[i][j].size = cell_height;
            board[i][j].startX = j * cell_width + center_variable_width;
            board[i][j].startY = i * cell_height + center_variable_height;
            DrawRectangle(board[i][j].startX, board[i][j].startY, 
                          board[i][j].size, board[i][j].size, 
                          board[i][j].color);
        }
    }

    if (!possible_moves.empty()) {
        for (unsigned int i = 0; i < possible_moves.size(); i++) {
            DrawRectangle(board[possible_moves[i].i][possible_moves[i].j].startX,
                          board[possible_moves[i].i][possible_moves[i].j].startY,
                          board[possible_moves[i].i][possible_moves[i].j].size,
                          board[possible_moves[i].i][possible_moves[i].j].size, 
                          move_cell);
        }
    }

    // Draw the pieces
    for (int i = 0; i < cell_number; i++) {
        for (int j = 0; j < cell_number; j++) {
            if(board[i][j].has_piece) {
                board[i][j].piece.draw(board[i][j].startX, board[i][j].startY, 
                                       board[i][j].size);
            }
        }
    }
}

/**
 * This function will put all of the pieces on the board.
 * 
 */
void Chess_board::put_pieces(){
    // Pawns
    for (int i = 0; i < cell_number; i++) {
        this->board[1][i].piece = Pawn(BLACKS);
        this->board[1][i].has_piece = true;

        this->board[6][i].piece = Pawn(WHITES);
        this->board[6][i].has_piece = true;
    }
    

    // Bishops
    board[0][2].piece = Bishop(BLACKS);
    board[0][2].has_piece = true;
    board[0][5].piece = Bishop(BLACKS);
    board[0][5].has_piece = true;
    board[7][2].piece = Bishop(WHITES);
    board[7][2].has_piece = true;
    board[7][5].piece = Bishop(WHITES);
    board[7][5].has_piece = true;

    // Knights
    board[0][1].piece = Knight(BLACKS);
    board[0][1].has_piece = true;
    board[0][6].piece = Knight(BLACKS);
    board[0][6].has_piece = true;
    board[7][1].piece = Knight(WHITES);
    board[7][1].has_piece = true;
    board[7][6].piece = Knight(WHITES);
    board[7][6].has_piece = true;

    // Rooks
    board[0][0].piece = Rook(BLACKS);
    board[0][0].has_piece = true;
    board[0][7].piece = Rook(BLACKS);
    board[0][7].has_piece = true;
    board[7][0].piece = Rook(WHITES);
    board[7][0].has_piece = true;
    board[7][7].piece = Rook(WHITES);
    board[7][7].has_piece = true;

    // Queens
    board[0][3].piece = Queen(BLACKS);
    board[0][3].has_piece = true;
    board[7][3].piece = Queen(WHITES);
    board[7][3].has_piece = true;

    // Kings
    board[0][4].piece = King(BLACKS);
    board[0][4].has_piece = true;
    board[7][4].piece = King(WHITES);
    board[7][4].has_piece = true;
}

/**
 * This function will reset the board to the original state.
 * 
 */
void Chess_board::reset_board() {
    // We check all of the cells to see if they have a piece on it and we eliminate it
    for (int i = 2; i < 6; i++) {
        for (int j = 0 ; j < 8; j++) {
            board[i][j].has_piece = false;
            try {
                board[i][j].piece.~Piece();
            }
            catch(const std::exception& e) {
            }
        }
    }
    //showMapCLI();
    this->put_pieces();
}

/**
 * This function will add a piece to a specific location.
 * 
 * @param[in] i will be the location on the y axes
 * @param[in] j will be the location on the x axes
 */
void Chess_board::add_piece(int i, int j) {
    // Change the Pawn into a Queen when reach the other side of the board
    if (i == 0 && temp_piece.team_of_piece() == WHITES 
        && temp_piece.get_piece_type() == PAWN) {
        temp_piece.~Piece();
        temp_piece = Queen(WHITES);
    }
    else if (i == 7 && temp_piece.team_of_piece() == BLACKS 
        && temp_piece.get_piece_type() == PAWN) {
        temp_piece.~Piece();
        temp_piece = Queen(BLACKS);
    }
    
    // Insert the new piese on the cell we want to move out piece to
    board[i][j].piece = temp_piece;
    board[i][j].has_piece = true;
    temp_piece.~Piece();
}

/**
 * This function will remove a piece from a specific location.
 * 
 * @param[in] i will be the location on the y axes
 * @param[in] j will be the location on the x axes
 */
void Chess_board::remove_piece(int i, int j){
    temp_piece = board[i][j].piece;
    board[i][j].piece.~Piece();
    board[i][j].has_piece = false;
}

/**
 * This function will get all the possible moves for a piece.
 * The function will call other functions to build a vector of possible moves.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 */
void Chess_board::get_moves(int i, int j){
    switch (this->temp_piece.get_piece_type()) {
    case NONE:
        break;
    
    case PAWN:
        this->possible_moves = this->pown_moves(i, j);
        break;
    
    case BISHOP:
        this->possible_moves = this->bishop_moves(i, j);
        break;

    case KNIGHT:
        this->possible_moves = this->knight_moves(i, j);
        break;

    case ROOK:
        this->possible_moves = this->rook_moves(i, j);
        break;

    case QUEEN:
        this->possible_moves = this->queen_moves(i, j);
        break;

    case KING:
        this->possible_moves = this->king_moves(i, j);
        break;
    }
}

/**
 * This function tell the state of a cell.
 * 
 * @param[in] i will be the location of the cell on the y axes
 * @param[in] j will be the location of the cell on the x axes
 * 
 * @returns The state of the cell. 
 * If it doesn't have a piece, it returns NO_PIECE (0).
 * If the piece is swhite, it returns WHITES (1).
 * If the piece is black, it returns BLACKS (2).
 */
cell_state_enum Chess_board::state_of_cell(int i, int j){
    if (board[i][j].has_piece) {
        if (board[i][j].piece.team_of_piece() == WHITES) {
            return WHITES;
        }
        return BLACKS;
    }
    return NO_PIECE;
}

/**
 * This function will return the with of a cell.
 * 
 * @returns The width of a cell.
 */
int Chess_board::get_cell_size(){
    return this->cell_width;
}

/**
 * This function will get all the possible moves for a POWN piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::pown_moves(int i, int j){
    std::vector<cell_coordinates> list;
    if(this->temp_piece.team_of_piece() == WHITES){
        // Move on empty cells
        if(i == 6){
            if(state_of_cell(i - 1, j) == NO_PIECE){
                list.push_back(cell_coordinates{i - 1, j});
                if(state_of_cell(i - 2, j) == NO_PIECE)
                    list.push_back(cell_coordinates{i - 2, j});
            }
        }
        else{
            if(i > 0 && state_of_cell(i - 1, j) == NO_PIECE)
                list.push_back(cell_coordinates{i - 1, j});
        }
        // Atack other pieces
        if(i > 0 && j > 0 && state_of_cell(i - 1, j - 1) == BLACKS)
            list.push_back(cell_coordinates{i - 1, j - 1});
        if(i > 0 && j < 7 && state_of_cell(i - 1, j + 1) == BLACKS)
            list.push_back(cell_coordinates{i - 1, j + 1});

        // TODO: Make the en percent move
        if (i < 3 && j < 7 && state_of_cell(i + 1, j + 1) == BLACKS)
            list.push_back(cell_coordinates{i - 1, j + 1});
        if (i < 3 && j > 0 && state_of_cell(i + 1, j - 1) == BLACKS)
            list.push_back(cell_coordinates{i - 1, j - 1});
    }
    // Move the black pawns
    else {
        // Move on empty cells
        if(i == 1){
            if(state_of_cell(i + 1, j) == NO_PIECE){
                list.push_back(cell_coordinates{i + 1, j});
                if(state_of_cell(i + 2, j) == NO_PIECE)
                    list.push_back(cell_coordinates{i + 2, j});
            }
        }
        else{
            if(i < 7 && state_of_cell(i + 1, j) == NO_PIECE)
                list.push_back(cell_coordinates{i + 1, j});
        }

        // Atack other pieces
        if(i < 7 && j > 0 && state_of_cell(i + 1, j - 1) == WHITES)
            list.push_back(cell_coordinates{i + 1, j - 1});
        if(i < 7 && j < 7 && state_of_cell(i + 1, j + 1) == WHITES)
            list.push_back(cell_coordinates{i + 1, j + 1});

        // TODO: Make the en percent move
        if (i > 4 && j > 0 && state_of_cell(i - 1, j - 1) == WHITES)
            list.push_back(cell_coordinates{i - 1, j - 1});
        if (i > 4 && j < 7 && state_of_cell(i - 1, j + 1) == WHITES)
            list.push_back(cell_coordinates{i - 1, j + 1});
    }

    return list;
}

/**
 * This function will get all the possible moves for a BISHOP piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::bishop_moves(int i, int j){
    std::vector<cell_coordinates> list;

    // Go Bottom Right
    int current_i = i, current_j = j;
    while(true){
        if(current_i < 7 && current_j < 7){
            current_i++;
            current_j++;
        }
        else
            break; 

        if(state_of_cell(current_i, current_j) == NO_PIECE)
            list.push_back(cell_coordinates{current_i, current_j});
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;    
    }

    // Go Bottom Left
    current_i = i, current_j = j;
    while(true){
        if(current_i < 7 && current_j > 0){
            current_i++;
            current_j--;
        }
        else
            break; 

        if(state_of_cell(current_i, current_j) == NO_PIECE)
            list.push_back(cell_coordinates{current_i, current_j});
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    // Go Top Right
    current_i = i, current_j = j;
    while(true){
        if(current_i > 0 && current_j < 7){
            current_i--;
            current_j++;
        }
        else
            break; 

        if(state_of_cell(current_i, current_j) == NO_PIECE)
            list.push_back(cell_coordinates{current_i, current_j});
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    // Go Top Left
    current_i = i, current_j = j;
    while(true){
        if(current_i > 0 && current_j > 0){
            current_i--;
            current_j--;
        }
        else
            break; 

        if(state_of_cell(current_i, current_j) == NO_PIECE)
            list.push_back(cell_coordinates{current_i, current_j});
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    return list;
}

/**
 * This function will get all the possible moves for a KNIGHT piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::knight_moves(int i, int j){
    std::vector<cell_coordinates> list;

    if(i - 1 >= 0 && j - 2 >= 0 && temp_piece.team_of_piece() != state_of_cell(i - 1, j - 2))
        list.push_back(cell_coordinates{i - 1, j - 2});

    if(i - 2 >= 0 && j - 1 >= 0 && temp_piece.team_of_piece() != state_of_cell(i - 2, j - 1))
        list.push_back(cell_coordinates{i - 2, j - 1});

    if(i - 2 >= 0 && j + 1 <= 7 && temp_piece.team_of_piece() != state_of_cell(i - 2, j + 1))
        list.push_back(cell_coordinates{i - 2, j + 1});

    if(i - 1 >= 0 && j + 2 <= 7 && temp_piece.team_of_piece() != state_of_cell(i - 1, j + 2))
        list.push_back(cell_coordinates{i - 1, j + 2});


    if(i + 1 <= 7 && j - 2 >= 0 && temp_piece.team_of_piece() != state_of_cell(i + 1, j - 2))
        list.push_back(cell_coordinates{i + 1, j - 2});
    
    if(i + 2 <= 7 && j - 1 >= 0 && temp_piece.team_of_piece() != state_of_cell(i + 2, j - 1))
        list.push_back(cell_coordinates{i + 2, j - 1});

    if(i + 2 <= 7 && j + 1 <= 7 && temp_piece.team_of_piece() != state_of_cell(i + 2, j + 1))
        list.push_back(cell_coordinates{i + 2, j + 1});

    if(i + 1 <= 7 && j + 2 <= 7 && temp_piece.team_of_piece() != state_of_cell(i + 1, j + 2))
        list.push_back(cell_coordinates{i + 1, j + 2});

    return list;
}

/**
 * This function will get all the possible moves for a ROOK piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::rook_moves(int i, int j){
    std::vector<cell_coordinates> list;

    int current_i = i, current_j = j;

    // Go Right
    while(true){
        if(current_j < 7)
            current_j++;
        else
            break;

        if(state_of_cell(current_i, current_j) == NO_PIECE){
            list.push_back(cell_coordinates{current_i, current_j});
        }
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    current_j = j;
    // Go Left
    while(true){
        if(current_j > 0)
            current_j--;
        else
            break;

        if(state_of_cell(current_i, current_j) == NO_PIECE){
            list.push_back(cell_coordinates{current_i, current_j});
        }
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    current_j = j;
    // Go Up
    while(true){
        if(current_i > 0)
            current_i--;
        else
            break;

        if(state_of_cell(current_i, current_j) == NO_PIECE){
            list.push_back(cell_coordinates{current_i, current_j});
        }
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }

    current_i = i;
    // Go Down
    while(true){
        if(current_i < 7)
            current_i++;
        else
            break;

        if(state_of_cell(current_i, current_j) == NO_PIECE){
            list.push_back(cell_coordinates{current_i, current_j});
        }
        else if(temp_piece.team_of_piece() != state_of_cell(current_i, current_j)){
            list.push_back(cell_coordinates{current_i, current_j});
            break;
        }
        else
            break;
    }
    
    return list;
}

/**
 * This function will get all the possible moves for a QUEEN piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::queen_moves(int i, int j){
    std::vector<cell_coordinates> list = this->bishop_moves(i, j);
    std::vector<cell_coordinates> list2 = this->rook_moves(i, j);

    for (unsigned int i = 0; i < list2.size(); i++)
        list.push_back(list2[i]);

    return list;
}

/**
 * This function will get all the possible moves for a KING piece.
 * 
 * @param[in] i will be the location of the piece on the y axes
 * @param[in] j will be the location of the piece on the x axes
 * 
 * @returns A vector that constains the cell coordinates of all the possible moves
 */
std::vector<cell_coordinates> Chess_board::king_moves(int i, int j){
    std::vector<cell_coordinates> list;

    for (int m = -1; m <= 1; m++) {
        for (int n = -1; n <= 1; n++) {
            if (m || n) {
                if (m + i < 8 && m + i >= 0 && n + j < 8 && n + j >= 0 && 
                    temp_piece.team_of_piece() != state_of_cell(m + i, n + j)) {
                    list.push_back(cell_coordinates{m + i, n + j});
                }
            }
        }
    }

    // Casteling
    if ((i == 0 || i == 7) && j == 4 ) {
        if(!this->board[i][j+1].has_piece && !this->board[i][j+2].has_piece
           && this->board[i][j+3].has_piece) {
            if(this->board[i][j+3].piece.get_piece_type() == ROOK) {
                list.push_back(cell_coordinates{i, j + 2});
            }
        }
        if(!this->board[i][j-1].has_piece && !this->board[i][j-2].has_piece
           && !this->board[i][j-3].has_piece && this->board[i][j-4].has_piece) {
            if(this->board[i][j+3].piece.get_piece_type() == ROOK) {
                list.push_back(cell_coordinates{i, j - 2});
            }
        }
    }

    //TODO: Move the Rook if there is a Casteling move
    //TODO: The king cannot move into a dangerous posotion

    return list;
}
