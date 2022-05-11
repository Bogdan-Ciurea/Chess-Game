
# Introduction

**Chess Game**

**This software was made by Bogdan Alexandru Ciurea**

**Email: ciureabogdanalexandru@yahoo.com**

This is a **personal project** that was the purpose of showing my skills in writing object-oriented code in C++ but also to show my interest in graphical applications.

----

# The software

## Used software
The presented software has been made using:
 - C++
 - Raylib (for graphics)
 - stackedit.io (for formatting the `.md` files)

## About the files
The project has the following structure:
```
├── assets
├── include
│   ├── cell.h
│   ├── cell_position.h
│   ├── chess.h
│   ├── chess_board.h
│   ├── move.h
│   ├── movement.h
│   ├── pieces.h
│   ├── raylib.h
│   ├── utils.h
├── lib
│   ├── libraylib.a
├── src
│   ├── cell.cpp
│   ├── cell_position.cpp
│   ├── chess_board.cpp
│   ├── functions.cpp
│   ├── main.cpp
│   ├── pieces.cpp
├── README.md
├── Makefile
├── FORMATTING.md
```

The folder named `assets` will contains the images and sounds for this project.
The file named `FORMATTING.md` has the coding standards that I've used. They criteria of choosing these coding standards was how I found fit.

## How to run this project

On **Linux** this project is still in development.

On **Windows**  you will need to run the Makefile and this would result in an `.exe` file being created.

## Drawbacks
In the current state of the program, the user will not be able to use 2 features that are still in development, mainly the en-passant move and the changing of the piece (when a pawn reaches the other end of the board).

The software does not have an AI so you will need at leas two players in order to play this game.

There is no sound. This is the least important drawback but I will consider adding it in the future.
