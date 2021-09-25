# Original makefile
default:
	g++ src/main.cpp src/Board.cpp src/Piece.cpp src/Functions.cpp -o Chess.exe -O2 -Wall -Wno-missing-braces -I include/ -I headers -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


# Name of the program that is build.
# Change this to something related to your task.
# If your task is too generic use some dummy nme like `program` or `app`.
TARGET_EXEC ?= chess

# Name of the test program (no need to update this).
TARGET_TEST ?= test

MKDIR_P ?= mkdir -p
BUILD_DIR ?= ./build

# This is the list of modules that implement your program logic. Modules in
# this list are used to build you program (together with src/main.c) and
# you unit test executable (together with tests/test_main.c)
common_SOURCES := src/Board.cpp src/Piece.cpp src/Functions.cpp

# This is the list of modules used to build your program.
program_SOURCES := $(common_SOURCES) \
               src/main.c

# This is the list of modules used to build the unit tests.
test_SOURCES := $(common_SOURCES) \
                tests/test_main.c

program_OBJS := $(program_SOURCES:%=$(BUILD_DIR)/%.o)
test_OBJS := $(test_SOURCES:%=$(BUILD_DIR)/%.o)

program_CFLAGS := -Iinclude headers -g -Wall -Werror -std=c11
test_CFLAGS := -Iinclude headers -g -Wall -std=c11

program_LDFLAGS := -Llib \

test_LDFLAGS := $(program_LDFLAGS) \
               -lcmocka

chess: $(BUILD_DIR)/$(TARGET_EXEC)

test: $(BUILD_DIR)/$(TARGET_TEST)

all: chess test

$(BUILD_DIR)/$(TARGET_EXEC): $(program_OBJS)
	$(CC) $(program_OBJS) -o $@  $(tas_LDFLAGS)

$(BUILD_DIR)/$(TARGET_TEST): $(test_OBJS)
	$(CC) $(test_OBJS) -o $@ $(test_LDFLAGS)
	$(BUILD_DIR)/$(TARGET_TEST)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(program_CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)