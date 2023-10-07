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
			~Board();
			Board(const Board &other);
			char* get_data();
			bool piece_placed(char symbol);
			bool add_piece(int x, int y, PuzzlePiece piece);
			bool is_invalid();
			bool is_solved();
			bool can_add_piece(int x, int y, PuzzlePiece piece);
			std::string to_string();
			int get_width();
			int get_height();
			void print_board();
			bool operator==(const Board &other);
		private:
			static int width;
			static int height;
			char data[60];
                        std::set<char> pieces;

	};
};


#endif
