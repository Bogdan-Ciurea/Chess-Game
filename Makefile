default:
	g++ src/main.cpp src/Board.cpp src/Piece.cpp src/Functions.cpp -o Chess.exe -O2 -Wall -Wno-missing-braces -I include/ -I headers -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm