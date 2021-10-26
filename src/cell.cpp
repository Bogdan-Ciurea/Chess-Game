#include "../include/cell.h"

/**
 * This function will be the constructor for the Cell class.
 * 
 */
Cell::Cell() {

}


/**
 * This function will be the constructor for the Cell class.
 * 
 * @param[in] col     Will represent the color of the cell
 * @param[in] cel_pos Will represent the position of the Cell (ex: a1)
 */
Cell::Cell(Color col, Cell_position celPos) {
    color = col;
    position = celPos;
}


/**
 * This function will be the deconstructor for the Cell class.
 * 
 */
Cell::~Cell() {

}