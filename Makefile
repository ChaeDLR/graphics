SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = rungraphics
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
CFLAGS = -Wall -O0 -g -std=c++20
LINKER_FLAGS = -lsdl2

all:
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)


clean:
	rm ./build/debug/rungraphics
