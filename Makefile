SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDES := include/

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
GCC := g++
CFLAGS := -Wall -O3 -std=c++17

ifdef DEBUG
CFLAGS += -g
endif

all: dir puzzle_solver

$(PIECES:%.o): %.cpp
	$(GCC) $(CFLAGS) $(SRC_DIR)$< -c -I$(INCLUDES)
dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
puzzle_solver: $(OBJ)
	$(GCC) $(CFLAGS) -lpthread $^ -o solve_puzzle -I $(INCLUDES) -o $(BIN_DIR)/solve_puzzle
run: all
	./puzzle_solver
Pieces.o: $(SRC_DIR)/Pieces.cpp
	$(GCC) $(CFLAGS) $< -c -I $(INCLUDES)
obj/main.o: src/main.cpp
	$(GCC) $(CFLAGS) $< -lpthread -c -I $(INCLUDES) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(GCC) $(CFLAGS) $< -c -I $(INCLUDES) -o $@
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
