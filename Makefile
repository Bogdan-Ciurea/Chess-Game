default:
	g++ src/main.cpp src/cell_position.cpp src/cell.cpp src/chess_board.cpp src/pieces.cpp src/functions.cpp -o Chess.exe -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm