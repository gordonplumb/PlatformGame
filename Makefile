CC = g++

COMPILER_FLAGS = -std=c++17 -w -I include -L lib -l SDL2-2.0.0 -l SDL2_ttf-2.0.0

OBJ_NAME = main

all :
	$(CC) src/* $(COMPILER_FLAGS) -o $(OBJ_NAME)

run : all 
	./$(OBJ_NAME)

debug :
	${CC} -DDEBUG src/* ${COMPILER_FLAGS} -o ${OBJ_NAME}
	./${OBJ_NAME}