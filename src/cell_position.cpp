#include "../include/cell_position.h"

/**
 * This function will be the constructor for the Cell_position class.
 * 
 * @param[in] chr Will represent the position on the x axis
 * @param[in] j   Will represent the position of the y axis
 * 
 */
Cell_position::Cell_position(char chr, int j){
    this->ch = chr;
    this->i = j;
}

/**
 * This function will be the constructor for the Cell_position class.
 * 
 */
Cell_position::Cell_position(){
    
}