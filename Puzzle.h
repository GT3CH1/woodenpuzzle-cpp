#ifndef PUZZLE_H
#define PUZZLE_H

#include "Board.h"
#include "puzzlepiece.h"
#include "Pieces.h"
#include <vector>
#include <tuple>
#include <map>
#include <iostream>
#include <fstream>

namespace puzzle {
    class Puzzle {
    public:
        std::tuple<bool, Board>
        solve(Board board, std::vector<PuzzlePiece> pieces, const std::set<PuzzlePiece> &placed_pieces);

        void set_all_solutions();

        void set_print_steps();

        void set_write_to_file();

        static std::map<uint, puzzle::Board> get_solutions();

        static std::vector<PuzzlePiece> pieces;

        clock_t begin;
        clock_t end;

        Puzzle();

        static void kill();

    private:
        bool all_solutions = false;
        bool print_steps = false;
        bool write_to_file = false;
    };
}
static bool kill_switch = false;
#endif
