PIECES := $(wildcard *Piece*.cpp)
SOURCES := $(PIECES:.cpp=.o)
GCC := g++
CFLAGS := -Wall -g

$(PIECES:%.o): %.cpp
	$(GCC) $(CFLAGS) $< -c
all: puzzle 
	./puzzle
Pieces.o: Pieces.cpp
	$(GCC) $(CFLAGS) $< -c
%.o: %.cpp
	$(GCC) $(CFLAGS) $< -c
puzzle: puzzlepiece.o Board.o Puzzle.o Pieces.o $(SOURCES)
	$(GCC) $(CFLAGS) -o puzzle $^
clean:
	rm -f *.o puzzle
