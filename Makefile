# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -g -Wall -Wno-missing-braces

# define any directories containing header files
INCLUDES = -I include/

# define library paths
# define any libraries to link into executable
# on windows
ifeq ($(OS),Windows_NT)
	LFLAGS = -L lib/ 
	LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

#on linux
else
	LFLAGS = 
	LIBS := -lraylib \
			-lGL \
			-lm \
			-lpthread \
			-ldl \
			-lrt \
			-lX11
endif

# define the C source files
SRCS := src/main.cpp\
 		src/cell_position.cpp\
  		src/cell.cpp\
  		src/chess_board.cpp \
   		src/pieces.cpp \
   		src/functions.cpp

# replacing the suffix .c of all words in the macro SRCS with the .o suffix
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
# on windows
ifeq ($(OS),Windows_NT)
	MAIN = Chess.exe
# on linux
else
	MAIN = chess
endif

.PHONY: depend clean

#all: $(MAIN)
#    @echo "Simple compiler named mycc has been compiled"

# on windows
ifeq ($(OS),Windows_NT)
	$(MAIN): $(OBJS) $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
# on linux
else
	$(MAIN): $(OBJS) $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)
endif

.c.o:
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
    $(RM) *.o *~ $(MAIN)

depend: $(SRCS)
    makedepend $(INCLUDES) $^