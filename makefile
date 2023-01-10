# windows MinGW32-make all to make include and src files
# windows MinGW32-make output to generate run.exe

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

# UTIL_INC_DIR = include/utility
UTIL_SRC_DIR = src/utility
UTIL_OBJ_DIR = obj/utility

C = g++
CFLAGS  = -c -Wall -I.
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-window -lsfml-system


SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

MAIN_OBJS_ENDING := $(filter-out $(SRC_DIR)/main.o, $(SRCS:%.cpp=%.o))
OBJS := $(MAIN_OBJS_ENDING:$(SRC_DIR)/%=$(OBJ_DIR)/%)

DEPS := $(shell find $(INC_DIR) -name '*.h' -or -name '*.hpp')

# .PHONY: all build clean



functional: $(OBJS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

util:  $(OBJS)
$(OBJ_DIR)/%.o: $(UTIL_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# VPATH=src:include
# CFLAGS=-I src:include

# run.exe to run main
output: $(SRC_DIR)/main.cpp $(OBJS) $(DEPS)
	g++ -o run $(SRC_DIR)/main.cpp $(OBJS) $(LDFLAGS)

build:
	mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR)
	mkdir -p $(UTIL_OBJ_DIR)
	cd ..

clean:
	rm -rf $(OBJS) run

fresh: clean build functional util output