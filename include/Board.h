#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <set>
#include "puzzlepiece.h"
namespace puzzle {
    /**
     * @brief Represents a 10x6 (WxH) board. Each board is represented by a vector of characters. The vector is 60
     * characters long and is initialized with the "empty" block, which is represented by the underscore character.
     * A board is "valid" as long as there are no holes in the board after a piece is placed. The board is solved once
     * all holes are filled.
     * @author GT3CH1
     */
    class Board {
    public:
        /**
         * Constructs a new 10x6 board.
         */
        Board();

        /**
         * Copy constructor
         * @param other The other Board to copy from.
         */
        Board(const Board &other);

        ~Board();

        /**
         * Gets whether a piece has already been placed on the board.
         * @param symbol The symbol used to represent the piece.
         * @return True if the piece has already been placed, false otherwise.
         */
        bool piece_placed(char symbol);

        /**
         * Adds a piece to the board at the given coordinates.
         * @param x The x coordinate on the board.
         * @param y The y coordinate on the board.
         * @param piece The piece to place.
         * @return True if the piece was successfully placed, false otherwise.
         */
        bool add_piece(int x, int y, PuzzlePiece piece);

        /**
         * Whether the current board state is invalid. A board is invalid if there are any holes along the x axis
         * in the board after a piece is placed.
         * @return True if the board is invalid, false otherwise.
         */
        bool is_invalid();

        /**
         * Whether the puzzle has been solved. A puzzle is solved when all holes in the board are filled and the state
         * is valid.
         * @return True if the puzzle is solved, false otherwise.
         */
        bool is_solved();

        /**
         * Whether the given piece can be placed at the given coordinates.
         * @param x The x coordinate on the board.
         * @param y The y coordinate on the board.
         * @param piece The piece to place.
         * @return True if the piece can be placed, false otherwise.
         */
        bool can_add_piece(int x, int y, PuzzlePiece piece);

        /**
         * Pretty prints the board.
         */
        void print_board();

        /**
         * Checks whether the board is equal to another board by comparing their data.
         * @param other The other board to compare.
         * @return True if the boards are equal, false otherwise.
         */
        bool operator==(const Board &other) const;

        /**
         * Checks whether the board is less than another board by comparing their data.
         * @param other The other board to compare.
         * @return True if the board is less than the other board, false otherwise.
         */
        bool operator<(const Board &other) const;

        /**
         * Assignment operator.
         * @param other The other board.
         * @return A reference to the board.
         */
        Board &operator=(const Board &other);


        /**
         * Gets the data on the board.
         * @return The data on the board.
         */
        std::vector<char> get_data();

        /**
         * Gets the data on the board in a pretty format.
         * @return The data on the board in a pretty format.
         */
        std::string get_pretty_data();

        /**
         * Gets how many seconds it took to get to this board state.
         * @return The number of seconds it took to get to this board state.
         */
        double get_time_to_solve() const;

        /**
         * Sets the number of seconds it took to solve this board.
         * @param time The number of seconds.
         */
        void set_time_to_solve(double time);

        /**
         * The hash value of this board.
         */
        uint hash;
    private:
        /**
         * The width of the board.
         */
        static int width;

        /**
         * The height of the board.
         */
        static int height;

        /**
         * The data on the board.
         */
        std::vector<char> data;

        /**
         * The available_pieces that have been placed on the board.
         */
        std::set<char> pieces;

        /**
         * The number of seconds it took to solve this board.
         */
        double time_to_solve;
    };
};


#endif
