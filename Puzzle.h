#ifndef PUZZLE_H
#define PUZZLE_H
#include "Board.h"
#include "puzzlepiece.h"
#include "Pieces.h"
#include <vector>
#include <tuple>
namespace puzzle {
	class Puzzle {
		public:
			static std::tuple<bool, Board> solve(Board board, std::vector<PuzzlePiece> pieces, std::set<PuzzlePiece> placed_pieces);
	};
}
#endif
