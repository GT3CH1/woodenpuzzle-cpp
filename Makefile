PIECES := $(wildcard *Piece*.cpp)
SOURCES := $(PIECES:.cpp=.o)
GCC := g++
CFLAGS := -Wall -O3 -std=c++17

ifdef DEBUG
CFLAGS = -Wall -g -std=c++17

endif

$(PIECES:%.o): %.cpp
	$(GCC) $(CFLAGS) $< -c
all: driver
driver: driver.cpp   Pieces.o puzzlepiece.o Puzzle.o Board.o $(SOURCES)
	$(GCC) $(CFLAGS)  $^ -o solve_puzzle
run: all
	./solve_puzzle
Pieces.o: Pieces.cpp
	$(GCC) $(CFLAGS) $< -c
%.o: %.cpp
	$(GCC) $(CFLAGS) $< -c
clean:
	rm -f *.o solve_puzzle solutions.txt
