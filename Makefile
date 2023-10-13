SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDES := include/

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ := $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
GCC := g++
CFLAGS := -Wall -Werror -Wpedantic -O3 -std=c++17

ifdef DEBUG
CFLAGS += -g
endif

all: dir puzzle_solver test

$(PIECES:%.o): %.cpp
	$(GCC) $(CFLAGS) $(SRC_DIR)$< -c -I$(INCLUDES)
dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
puzzle_solver: $(OBJ)
	$(GCC) $(CFLAGS) -lpthread $^ -o solve_puzzle -I $(INCLUDES) -o $(BIN_DIR)/wooden_puzzle
Pieces.o: $(SRC_DIR)/Pieces.cpp
	$(GCC) $(CFLAGS) $< -c -I $(INCLUDES)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(GCC) $(CFLAGS) $< -c -I $(INCLUDES) -o $@
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) ./bin/test
test: dir puzzle_solver
	$(GCC) $(CFLAGS) test/Test.cpp -lgtest -lgtest_main $(TEST_OBJ) -o bin/test -I $(INCLUDES)
	./bin/test
