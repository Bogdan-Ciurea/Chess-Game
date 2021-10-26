#include "../include/movement.h"

#include <cmath>
#include <vector>

/**
 * This function will get the coordinates of a cell depending on
 * where on the screen the user the player clicked.
 * 
 * @returns The coordinates of the cell that is clicked
 */
cell_coordinates get_cell(){
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    // These variable will tell us the size of a cell
    int cell_width = screen_width / 8;
    int cell_height = screen_height / 8;

    // These variables will help us center the board to middle the window
    int center_variable_width = 0;
    int center_variable_height = 0;

    // Will center the board
    if (screen_width > screen_height){
        center_variable_width = (screen_width - screen_height) / 2;
        center_variable_height = 0;
        cell_width = cell_height;
    }
    else{
        center_variable_height = (screen_height - screen_width) / 2;
        center_variable_width = 0;
        cell_height = cell_width;
    }

    Vector2 coordinates = GetMousePosition();

    if(coordinates.x < center_variable_width || coordinates.y < center_variable_height)
        return cell_coordinates{-1, -1};

    for(int i = 1; i < 9; i++)
        for(int j = 1; j < 9; j++)
            if(j * cell_width + center_variable_width > coordinates.x && 
                i * cell_height + center_variable_height > coordinates.y)
                return cell_coordinates{--i, --j};

    return cell_coordinates{-1, -1};
}

/**
 * This function will check if a set of coordinates are in a vector of coordinates.
 * 
 * @param[in] elem will be the set coordinates that we search for
 * @param[in] vec  will be the vector of coordinates
 * 
 * @returns TRUE if the set is in the vector. FALSE otherweise
 */
bool element_in_vector(cell_coordinates elem, std::vector<cell_coordinates> vec){
    for(unsigned int i = 0; i < vec.size(); i++)
        if(vec[i].i == elem.i && vec[i].j == elem.j)
            return true;
    return false;
}
