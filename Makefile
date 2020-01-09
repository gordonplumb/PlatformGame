OBJS = src/main.cpp src/texturewrapper.cpp src/abstractentity.cpp src/player.cpp 

CC = g++

COMPILER_FLAGS = -std=c++14 -w -I include -L lib -l SDL2-2.0.0

OBJ_NAME = main

all : $(OBJS)
	$(CC) src/* $(COMPILER_FLAGS) -o out/$(OBJ_NAME)

run : all 
	out/./$(OBJ_NAME)
