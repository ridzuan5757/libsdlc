OBJS = main.cpp
CC = g++
INCLUDE_PATHS = -IC:/mingw_dev_lib/include/SDL2
LIBRARY_PATHS = -LC:/mingw_dev_lib/lib
COMPILER_FLAGS = -w
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
