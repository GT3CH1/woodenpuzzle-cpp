#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <set>
#include "puzzlepiece.h"

namespace puzzle {
    class Board {
    public:
        Board();

        Board(const Board &other);

        ~Board();

        bool piece_placed(char symbol);

        bool add_piece(int x, int y, PuzzlePiece piece);

        bool is_invalid();

        bool is_solved();

        bool can_add_piece(int x, int y, PuzzlePiece piece);

        void print_board();

        bool operator==(const Board &other) const;

        bool operator<(const Board &other) const;

        Board &operator=(const Board &other);

        char *get_data();

        std::string get_pretty_data();

        double get_time_to_solve();

        void set_time_to_solve(double time);

        uint hash;
    private:
        static int width;
        static int height;
        char *data;
        std::set<char> pieces;
        float time_to_solve;

    };
};


#endif
