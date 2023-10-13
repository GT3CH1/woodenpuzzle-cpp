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
#include <chrono>

namespace puzzle {
    /**
     * The main puzzle class used to solve the puzzle board. This drives a recursive algorithm used to bruteforce the
     * puzzle.
     * @author GT3CH1
     */
    class Puzzle {
    public:

        /**
         * The main recursive function used to solve the puzzle.
         * @return A tuple containing whether the puzzle was solved and the board state.
         */
        std::tuple<bool, Board> solve();

        /**
         * Sets whether to continue the algorithm after finding a solution.
         */
        void set_all_solutions();

        /**
         * Sets whether to print the steps taken to solve the puzzle.
         */
        void set_print_steps();

        /**
         * Sets whether to write the solution and statistics to `solutions.txt`.
         */
        void set_write_to_file();

        /**
         * The map of solutions found by the algorithm.
         * @return A map containing any solutions found by the algorithm.
         */
        static std::map<uint, puzzle::Board> get_solutions();


        /**
         * Creates a new puzzle object.
         */
        Puzzle();
	
	/**
	 * Creates a puzzle object with a list of pieces to use.
	 * @param pieces The list of pieces to use.
	 */
        Puzzle(std::vector<PuzzlePiece> &pieces);

        /**
         * Enables the kill switch to stop the algorithm in the event of a signal.
         */
        static void kill();

	/**
	 * Sets the thread id of the puzzle.
	 * @param id The thread id.
	 */
        void set_thread_id(int id);

	/**
	 * Returns the thread id used by the puzzle.
	 * @return The thread id.
	 */
        int get_thread_id();

    private:
        /**
         * Whether to continue the algorithm after finding a solution.
         */
        bool all_solutions = false;

        /**
         * Whether to print the steps taken to solve the puzzle.
         */
        bool print_steps = false;

        /**
         * Whether to write the solution and statistics to `solutions.txt`.
         */
        bool write_to_file = false;
	
        /**
         * The thread id.
         */
        int thread_id = 0;

        /**
         * The list of available pieces to use.
         */
        std::vector<PuzzlePiece> available_pieces;

        /**
         * The time helper used for the puzzle.
         */
        TimeHelper time_helper;

        /**
         * Recursive function used to solve the puzzle.
         * @param board The current board state.
         * @param pieces The current list of available_pieces that are available to be placed.
         * @param placed_pieces The current list of available_pieces that have been placed.
         * @return
         */
        std::tuple<bool, Board>
        solve(Board board, const std::vector<PuzzlePiece> &pieces, const std::set<PuzzlePiece> &placed_pieces);
    };
}
[[maybe_unused]]
/**
 * The kill switch used to stop the algorithm in the event of a signal.
 */
static bool kill_switch = false;


#endif
