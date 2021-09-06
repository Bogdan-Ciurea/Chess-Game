#include "../headers/movementHeader.h"
#include "../headers/mapHeader.h"

#include <cmath>
#include<iostream>
#include<vector>

cellCoordinates getCell(){
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int cellWidth = screenWidth / 8;  //These variable will tell us
    int cellHeight = screenHeight / 8; // the size of a cell

    int centerVariableWidth = 0; // These variables will help us 
    int centerVariableHeight = 0; // center the board to middle the window 

    // Will center the board
    if (screenWidth > screenHeight){
        centerVariableWidth = (screenWidth - screenHeight) / 2;
        centerVariableHeight = 0;
        cellWidth = cellHeight;
    }
    else{
        centerVariableHeight = (screenHeight - screenWidth) / 2;
        centerVariableWidth = 0;
        cellHeight = cellWidth;
    }

    Vector2 coordinates = GetMousePosition();

    if(coordinates.x < centerVariableWidth || coordinates.y < centerVariableHeight)
        return cellCoordinates{-1, -1};

    for(int i = 1; i < 9; i++)
        for(int j = 1; j < 9; j++)
            if(j * cellWidth + centerVariableWidth > coordinates.x && 
                i * cellHeight + centerVariableHeight > coordinates.y)
                return cellCoordinates{--i, --j};

    return cellCoordinates{-1, -1};
}

bool elementInVector(cellCoordinates elem, std::vector<cellCoordinates> vec){
    for(int i = 0; i < vec.size(); i++)
        if(vec[i].i == elem.i && vec[i].j == elem.j)
            return true;
    return false;
}
