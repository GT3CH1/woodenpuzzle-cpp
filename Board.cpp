#include "Board.h"

using namespace puzzle;
int Board::width = 10;
int Board::height = 6;

Board::Board() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->data[i * 10 + j] = '_';
        }
    }
    pieces = std::set<char>();
}

Board::Board(const Board &other) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->data[i * 10 + j] = other.data[i * 10 + j];
        }
    }
    this->pieces = std::set<char>(other.pieces);
}

Board::~Board() {
    // TODO Auto-generated destructor stub
}

char *Board::get_data() {
    return this->data;
}

bool Board::piece_placed(char symbol) {
    return pieces.find(symbol) != pieces.end();
}

bool Board::can_add_piece(int x, int y, PuzzlePiece piece) {
    if (x < 0 || x > 9 || y < 0 || y > 5 || this->piece_placed(piece.get_symbol())) {
        return false;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece.get_data()[i * 5 + j] != '_') {
                if ((x + j) > 9 || (y + i) * 10 > 59) {
                    return false;
                }
                if (this->data[(y + i) * 10 + (x + j)] != '_') {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::add_piece(int x, int y, PuzzlePiece piece) {
    if (!this->can_add_piece(x, y, piece)) {
        return false;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece.get_data()[i * 5 + j] != '_')
                this->data[(y + i) * 10 + (x + j)] = piece.get_symbol();
        }
    }
    this->pieces.insert(piece.get_symbol());
    return true;
}


bool Board::is_invalid() {
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 10; x++) {
            auto current_symbol = this->data[y * 10 + x];
            if (current_symbol == '_') {
                continue;
            } else {
                for (int xx = x + 1; xx < 10; xx++) {
                    if (this->data[y * 10 + xx] == '_') {
                        return true;
                    }
                }
            }
        }
    }
    // check corners if they are empty but have a piece next to them
    if (this->data[0] == '_' && this->data[1] != '_' && this->data[10] != '_') {
        return true;
    }
    if (this->data[9] == '_' && this->data[8] != '_' && this->data[19] != '_') {
        return true;
    }
    if (this->data[50] == '_' && this->data[51] != '_' && this->data[40] != '_') {
        return true;
    }
    if (this->data[59] == '_' && this->data[58] != '_' && this->data[49] != '_') {
        return true;
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
    for (int i = 0; i < this->height; i++) {
        std::string row = "|";
        for (int j = 0; j < this->width; j++) {
            row += this->data[i * 10 + j];
        }
        row += "|";
        std::cout << row << std::endl;
    }
    std::cout << top_border << std::endl;

}

bool Board::operator==(const Board &other) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->data[i * 10 + j] != other.data[i * 10 + j]) {
                return false;
            }
        }
    }
    return true;
}

bool Board::operator<(const Board &other) const {
    return this->pieces.size() < other.pieces.size();
}

bool Board::is_solved() {
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 10; x++) {
            if (this->data[y * 10 + x] == '_') {
                return false;
            }
        }
    }
    return true;
}
