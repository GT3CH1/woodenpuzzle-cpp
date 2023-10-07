#include "Board.h"
using namespace puzzle;
int Board::width = 10;
int Board::height = 6;
Board::Board() {
	for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			this->data[i*10+j] = '_';
		}
	}
	pieces = std::set<char>();
}

Board::Board(const Board& other) {
	for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			this->data[i*10+j] = other.data[i*10+j];
		}
	}
	this->pieces = std::set<char>(other.pieces);
}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

char* Board::get_data() {
	return this->data;
}

bool Board::piece_placed(char symbol) {
	return pieces.count(symbol);
}

bool Board::can_add_piece(int x, int y, PuzzlePiece piece) {
	if (x < 0 || x > 9 || y < 0 || y > 5 || this->piece_placed(piece.get_symbol())) {
		return false;
	}
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j ++) {
			if(piece.get_data()[i*5+j] != '_') {
				if( (x+j) > 9 || (y+i)*10 > 59) {
					return false;
				}
				if(this->data[(y+i)*10+(x+j)] != '_') {
					return false;
				}
			}
		}
	}

	return true;
}

bool Board::add_piece(int x, int y, PuzzlePiece piece) {
	if(!this->can_add_piece(x, y, piece)){
		return false;
	}
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if (piece.get_data()[i*5+j] != '_')
				this->data[(y+i)*10+(x+j)] = piece.get_symbol();
		}
	}
	this->pieces.insert(piece.get_symbol());
	return true;
}


bool Board::is_invalid() {
	for(int y = 0 ; y < 6; y++) {
		bool found_piece = false;
		for(int x = 0; x < 10; x++) {
			if(this->data[y*10+x] != '_') {
				if (!found_piece) {
					found_piece = true;
				}
				continue;
			}
			if(this->data[y*10+x] == '_' && found_piece) {
				return true;
			}
			else if (x == 0 && y == 0) {
				if (this->data[1] != '_' && this->data[10] != '_') {
					return true;
				}
			}
			else if (x == 9 && y == 0) {
				if (this->data[8] != '_' && this->data[19] != '_' ) {
					return true;
				}
			}

			else if (x == 0 && y == 5) {
				if(this->data[40] != '_' && this->data[51] != '_') {
					return true;
				}
			}

			else if (x == 9 and y == 5) {
				if(this->data[49] != '_' && this->data[58] != '_') {
					return true;
				}
			}

			else if ( x >= 1 && x < 9 && y >= 1 && y < 5) {
				if(this->data[y*10+x-1] != '_' && this->data[y*10+x+1] != '_' && this->data[(y-1)*10+x] != '_' && this->data[(y+1)*10+x] != '_') {
					return true;
				}
			}

			else if ( x >= 1 && x < 9 && y == 5 ) {
				if(this->data[y*10+x-1] != '_' && this->data[y*10+x+1] != '_' && this->data[(y-1)*10+x] != '_') {
					return true;
				}
			}

		}
	}
	return false;
}


void Board::print_board() {
	// top border
	std::string top_border = "+";
	for (int i = 0; i < this->width; i++) {
		top_border += "-";
	}
	top_border += "+";
	std::cout << top_border << std::endl;
	for(int i = 0; i < this->height; i++) {
		std::string row = "|";
		for(int j = 0; j < this->width; j++) {
			row += this->data[i*10+j];
		}
		row += "|";
		std::cout << row << std::endl;
	}
	std::cout << top_border << std::endl;

}

bool Board::operator==(const Board &other) {
	for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			if(this->data[i*6+j] != other.data[i*6+j]) {
				return false;
			}
		}
	}
	return true;
}

bool Board::is_solved() {
	for(int y = 0 ; y<6; y++) {
		for(int x = 0; x < 10; x++) {
			if(this->data[y*6+x] == '_') {
				return false;
			}
		}
	}
	return true;
}
